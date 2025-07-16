#!/bin/bash
set -e

FAM_FILE="$1"

if [ ! -f "$FAM_FILE" ]; then
  echo "❌ FAM file not found: $FAM_FILE"
  exit 1
fi

REQUIRED_KEYS=("name" "app_id" "entry_point")
MISSING=()

for key in "${REQUIRED_KEYS[@]}"; do
  if ! grep -E "^\s*${key}\s*=" "$FAM_FILE" > /dev/null; then
    MISSING+=("$key")
  fi
done

if [ ${#MISSING[@]} -ne 0 ]; then
  echo "❌ Missing keys in $FAM_FILE:"
  for k in "${MISSING[@]}"; do echo "  - $k"; done
  exit 1
fi

echo "✅ $FAM_FILE is valid"
