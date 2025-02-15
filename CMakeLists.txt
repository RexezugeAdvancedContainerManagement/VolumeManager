cmake_minimum_required(VERSION 3.15)

# Include Conan toolchain first
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

project(FruitExample LANGUAGES CXX)

# C++17 configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies (crucial addition)
find_package(fruit REQUIRED)

# Create executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Greeter.cpp
    include/IGreeter.h
    src/Greeter.h
)

# Link dependencies
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE fruit::fruit)
