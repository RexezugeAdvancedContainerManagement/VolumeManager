cmake_minimum_required(VERSION 3.15)
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
project(FruitExample LANGUAGES CXX)

# C++ standard configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(fruit REQUIRED)
find_package(GTest REQUIRED)

# Configure library sources (exclude main.cpp)
file(GLOB LIB_SOURCES "src/*.cpp")
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Configure headers
file(GLOB HEADERS "include/*.h" "src/*.h")

# Core library containing business logic
add_library(fruit_lib STATIC
    ${LIB_SOURCES}
    ${HEADERS}
)

# Public include directories (propagate to dependents)
target_include_directories(fruit_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Public linking for transitive dependencies
target_link_libraries(fruit_lib PUBLIC 
    fruit::fruit
)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    fruit_lib
)

# ------------------- Testing Section -------------------
enable_testing()

# Test executable configuration
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(tests ${TEST_SOURCES})

# Test dependencies and includes
target_link_libraries(tests PRIVATE
    GTest::GTest
    GTest::Main
    fruit_lib  # Link to library NOT main executable
)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Register with CTest
add_test(NAME ExampleTests COMMAND tests)
