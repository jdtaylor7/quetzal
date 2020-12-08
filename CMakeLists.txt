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

# Compile object library.
add_library(quetzal_obj OBJECT src/quetzal.cpp)
target_compile_options(quetzal_obj PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -DSTM32F103xB
    -O2
    -fno-rtti
    -fno-exceptions)

# Link executable.
add_executable(quetzal_elf)
target_link_options(quetzal_elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -T${CMAKE_SOURCE_DIR}/linkerscript.ld
    -nostartfiles)
target_link_libraries(quetzal_elf quetzal_obj)

# Run custom command for objcopy.
add_custom_command(
    TARGET quetzal_elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/quetzal_elf ${CMAKE_CURRENT_BINARY_DIR}/quetzal
)
