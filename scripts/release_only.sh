#!/bin/bash

# Exit on any error
set -e

# Define build directory
RELEASE_BUILD_DIR="build-release"

# Clean and create build directory
rm -rf "${RELEASE_BUILD_DIR}"
mkdir -p "${RELEASE_BUILD_DIR}"

echo "=== BUILDING (RELEASE) ==="
cd "${RELEASE_BUILD_DIR}"

# Install dependencies and configure the project
conan install .. --build=missing --output-folder=.
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
cmake --build .

cd ..
echo "=== RELEASE BUILD COMPLETED SUCCESSFULLY ==="
