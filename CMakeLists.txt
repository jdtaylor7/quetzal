cmake_minimum_required(VERSION 3.10)

# Set project name.
project(quetzal VERSION 0.1.0)

# Specify C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories.
include_directories(
    "${PROJECT_SOURCE_DIR}/include/cmsis"
    "${PROJECT_SOURCE_DIR}/include/stm32f1xx"
)

# Add executables.
add_executable(quetzal src/quetzal.cpp)

# Add compiler options.
target_compile_options(quetzal PRIVATE -O2)
