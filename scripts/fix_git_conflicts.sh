#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT_DIR"

echo "[1/4] Detecting unfinished git operations..."
if [[ -f .git/MERGE_HEAD ]]; then
  echo "- merge in progress: aborting"
  git merge --abort || true
fi
if [[ -d .git/rebase-apply || -d .git/rebase-merge ]]; then
  echo "- rebase in progress: aborting"
  git rebase --abort || true
fi
if [[ -f .git/CHERRY_PICK_HEAD ]]; then
  echo "- cherry-pick in progress: aborting"
  git cherry-pick --abort || true
fi


echo "[2/4] Scanning for conflict markers..."
if rg -n "^(<<<<<<<|=======|>>>>>>>)" --glob '!build/**' --glob '!dist/**'; then
  echo "ERROR: Conflict markers found. Resolve files above, then commit."
  exit 2
else
  echo "- no conflict markers found"
fi

echo "[3/4] Validating repository state..."
git update-index -q --refresh
if ! git diff-files --quiet; then
  echo "ERROR: unstaged tracked-file changes exist"
  git status --short
  exit 3
fi
if ! git diff-index --cached --quiet HEAD --; then
  echo "ERROR: staged-but-uncommitted changes exist"
  git status --short
  exit 4
fi

echo "[4/4] Repository is conflict-free and publish-ready"
git status -sb
