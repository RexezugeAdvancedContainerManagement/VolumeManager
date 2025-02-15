#!/bin/bash

# Exit on any error
set -e

# Define build directories
DEBUG_BUILD_DIR="build-debug"
RELEASE_BUILD_DIR="build-release"

echo "=== CLEANING BUILD DIRECTORIES ==="

# Remove both debug and release build directories
rm -rf "${DEBUG_BUILD_DIR}" "${RELEASE_BUILD_DIR}"

echo "=== CLEANING COMPLETED SUCCESSFULLY ==="
