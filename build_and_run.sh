#!/bin/bash

# Exit immediately on error
set -e

# Define build directories
DEBUG_BUILD_DIR="build-debug"
RELEASE_BUILD_DIR="build-release"

# Clean and create directories
rm -rf "${DEBUG_BUILD_DIR}" "${RELEASE_BUILD_DIR}"
mkdir -p "${DEBUG_BUILD_DIR}" "${RELEASE_BUILD_DIR}"

# Function: build_and_test (Debug)
build_and_test() {
    echo "=== BUILDING AND TESTING (DEBUG) ==="
    cd "${DEBUG_BUILD_DIR}"
    conan install ../.. --build=missing -s build_type=Debug --output-folder=.
    cmake ../.. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
    cmake --build .
    ctest --output-on-failure
    cd ..
}

# Function: build_and_run (Release)
build_and_run() {
    echo "=== BUILDING AND RUNNING (RELEASE) ==="
    cd "${RELEASE_BUILD_DIR}"
    conan install ../.. --build=missing --output-folder=.
    cmake ../.. -DCMAKE_BUILD_TYPE=Release
    cmake --build .
    echo "=== RUNNING PROGRAM ==="
    ./FruitExample
    cd ..
}

# Main execution flow
build_and_test && build_and_run

echo "=== ALL OPERATIONS COMPLETED SUCCESSFULLY ==="
