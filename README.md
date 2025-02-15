# Clean build
rm -rf build && mkdir build && cd build

# Install dependencies
conan install .. --build=missing --output-folder=.

# Configure & build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

# Run
./FruitExample
