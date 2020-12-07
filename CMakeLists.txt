cmake_minimum_required(VERSION 3.10)

# Set project name.
project(quetzal VERSION 0.1.0)

message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")

# Specify C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories.
include_directories(
    "${PROJECT_SOURCE_DIR}/include/cmsis"
    "${PROJECT_SOURCE_DIR}/include/stm32f1xx"
)

# Link exectable into object library.
add_library(quetzal_obj OBJECT ./src/quetzal.cpp)
target_compile_options(quetzal_obj PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -DSTM32F103xB
    -O2
    -fno-rtti
    -fno-exceptions)

# # Add executables.
# # set(LINKER_SCRIPT linkerscript.ld)
# add_executable(quetzal_elf)
# target_compile_options(quetzal_elf PRIVATE
#     -mcpu=cortex-m3
#     -mthumb
#     -Tlinkerscript.ld  # necessary?
#     -nostartfiles)
# target_link_libraries(quetzal_elf quetzal_obj)
#
# # Add custom command for objcopy.
# add_custom_command(OUTPUT quetzal
#     COMMAND objcopy -O binary ${CMAKE_CURRENT_BINARY_DIR}/quetzal_elf ${CMAKE_CURRENT_BINARY_DIR}/quetzal)
