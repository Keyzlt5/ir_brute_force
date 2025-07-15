#!/usr/bin/env bash

# Basic validation script for IR Brute Force app FAP file
set -e

FAP_PATH="flipperzero-firmware/build/f7-firmware-D/.extapps/ir_brute_force.fap"

echo "🔍 Checking if IR Brute Force FAP exists..."

if [ ! -f "$FAP_PATH" ]; then
  echo "❌ ERROR: FAP file not found at $FAP_PATH"
  exit 1
fi

if [ ! -s "$FAP_PATH" ]; then
  echo "❌ ERROR: FAP file exists but is empty"
  exit 1
fi

echo "✅ IR Brute Force FAP found and valid: $FAP_PATH"

# Optional: print file size
FILE_SIZE=$(stat -c%s "$FAP_PATH")
echo "📦 File size: $FILE_SIZE bytes"
