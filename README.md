# Clean build
rm -rf build && mkdir build && cd build

# Install dependencies
conan install .. --build=missing --output-folder=.

# Configure & build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Run
./FruitExample

# ==== Testing
rm -rf build && mkdir build && cd build
conan install .. --build=missing -s build_type=Debug --output-folder=.
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
cmake --build .
ctest --output-on-failure
