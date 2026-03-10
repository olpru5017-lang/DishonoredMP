#!/usr/bin/env bash
set -euo pipefail

BASE_REF="${1:-origin/main}"

if [[ -z "$(git rev-parse --is-inside-work-tree 2>/dev/null)" ]]; then
  echo "Run inside a git repository." >&2
  exit 1
fi

if ! git diff --quiet || ! git diff --cached --quiet; then
  echo "Working tree is not clean. Commit/stash changes first." >&2
  git status --short
  exit 2
fi

echo "Fetching remotes..."
git fetch --all --prune

echo "Merging ${BASE_REF} into $(git branch --show-current)..."
set +e
git merge --no-ff --no-edit "${BASE_REF}"
MERGE_CODE=$?
set -e

if [[ ${MERGE_CODE} -eq 0 ]]; then
  echo "Merge completed without conflicts."
  exit 0
fi

CONFLICTS=$(git diff --name-only --diff-filter=U)
if [[ -z "${CONFLICTS}" ]]; then
  echo "Merge failed, but no conflicted files detected."
  exit ${MERGE_CODE}
fi

echo "Conflicted files:" 
echo "${CONFLICTS}"

AUTO_FILES=(
  "CMakeLists.txt"
  "README.md"
  "scripts/make_one_file.sh"
)

UNRESOLVED=0
while IFS= read -r file; do
  [[ -z "${file}" ]] && continue
  AUTO=0
  for auto_file in "${AUTO_FILES[@]}"; do
    if [[ "${file}" == "${auto_file}" ]]; then
      AUTO=1
      break
    fi
  done

  if [[ ${AUTO} -eq 1 ]]; then
    echo "Auto-resolving ${file} with current branch version (--ours)"
    git checkout --ours -- "${file}"
    git add "${file}"
  else
    echo "Needs manual resolution: ${file}"
    UNRESOLVED=1
  fi
done <<< "${CONFLICTS}"

if [[ ${UNRESOLVED} -eq 1 ]]; then
  echo "Some files still need manual conflict resolution."
  git status --short
  exit 3
fi

git commit -m "Resolve PR merge conflicts against ${BASE_REF}"
echo "Conflicts resolved and merge commit created."
