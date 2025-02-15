#!/bin/bash

# Exit on any error
set -e

# Define build directory
DEBUG_BUILD_DIR="build-debug"

# Clean and create build directory
rm -rf "${DEBUG_BUILD_DIR}"
mkdir -p "${DEBUG_BUILD_DIR}"

echo "=== BUILDING AND TESTING (DEBUG) ==="
cd "${DEBUG_BUILD_DIR}"

# Install dependencies and configure the project
conan install .. --build=missing -s build_type=Debug --output-folder=.
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

# Build and test
cmake --build .
ctest --output-on-failure

cd ..
echo "=== DEBUG BUILD AND TESTING COMPLETED SUCCESSFULLY ==="
