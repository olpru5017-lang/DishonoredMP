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

if [[ -f "${BUILD_DIR}/dishonored_mp.dll" ]]; then
  cp "${BUILD_DIR}/dishonored_mp.dll" "${PKG_DIR}/dishonored_mp.dll"
elif [[ -f "${BUILD_DIR}/Release/dishonored_mp.dll" ]]; then
  cp "${BUILD_DIR}/Release/dishonored_mp.dll" "${PKG_DIR}/dishonored_mp.dll"
elif [[ -f "${BUILD_DIR}/libdishonored_mp.so" ]]; then
  cp "${BUILD_DIR}/libdishonored_mp.so" "${PKG_DIR}/libdishonored_mp.so"
else
  echo "ERROR: Plugin binary not found in build output." >&2
  exit 1
fi

cp "${ROOT_DIR}/dishonored_mp.cfg" "${PKG_DIR}/dishonored_mp.cfg"
cat > "${PKG_DIR}/INSTALL.txt" <<'TXT'
DishonoredMP quick install

1) Copy the plugin file (dishonored_mp.dll on Windows) into Dishonored game folder.
2) Copy dishonored_mp.cfg next to the plugin.
3) Start the game. The mod initializes automatically and injects Multiplayer button in main menu.
TXT

(
  cd "${PKG_DIR}"
  cmake -E tar cfv "${ZIP_PATH}" --format=zip .
)

echo "Ready: ${ZIP_PATH}"
