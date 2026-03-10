#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
DIST_DIR="${ROOT_DIR}/dist"
PKG_DIR="${DIST_DIR}/dishonored_mp_package"
ZIP_PATH="${DIST_DIR}/dishonored_mp_package.zip"

cmake -S "${ROOT_DIR}" -B "${BUILD_DIR}" -DDMP_BUILD_TESTS=OFF
cmake --build "${BUILD_DIR}" --config Release

rm -rf "${PKG_DIR}" "${ZIP_PATH}"
mkdir -p "${PKG_DIR}"

if [[ -f "${BUILD_DIR}/dinput8.dll" ]]; then
  cp "${BUILD_DIR}/dinput8.dll" "${PKG_DIR}/dinput8.dll"
elif [[ -f "${BUILD_DIR}/Release/dinput8.dll" ]]; then
  cp "${BUILD_DIR}/Release/dinput8.dll" "${PKG_DIR}/dinput8.dll"
elif [[ -f "${BUILD_DIR}/libdinput8.so" ]]; then
  cp "${BUILD_DIR}/libdinput8.so" "${PKG_DIR}/libdinput8.so"
else
  echo "ERROR: Proxy plugin binary not found in build output." >&2
  exit 1
fi

cp "${ROOT_DIR}/dishonored_mp.cfg" "${PKG_DIR}/dishonored_mp.cfg"
cat > "${PKG_DIR}/INSTALL.txt" <<'TXT'
DishonoredMP quick install (auto-load)

1) Copy dinput8.dll into Dishonored\Binaries\Win32.
2) Copy dishonored_mp.cfg next to dinput8.dll.
3) Start the game. The mod initializes automatically through dinput8 proxy loading.
4) Check dishonored_mp.log to confirm successful startup.

Important:
- If another mod already uses dinput8.dll, you must chain-load or merge proxies.
TXT

(
  cd "${PKG_DIR}"
  cmake -E tar cfv "${ZIP_PATH}" --format=zip .
)

echo "Ready: ${ZIP_PATH}"
