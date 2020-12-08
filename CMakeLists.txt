cmake_minimum_required(VERSION 3.10)

# Set project name.
project(quetzal VERSION 0.1.0)

# Set variables.
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linkerscript.ld)

# Specify C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories.
include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/cmsis"
    "${PROJECT_SOURCE_DIR}/include/stm32f1xx"
)

# Compile object library.
add_library(quetzal_obj OBJECT src/quetzal.cpp)
target_compile_options(quetzal_obj PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -O2
    -fno-rtti
    -fno-exceptions
    -Wall
    -Wextra
    -Werror
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wformat-overflow
    -Wformat-truncation=2
    -Wundef
    -fno-common
    -fstack-usage
    # -Wstack-usage=<stack_size>
    -Wconversion
    -ffunction-sections
    -fdata-sections
)
target_compile_definitions(quetzal_obj PRIVATE -DSTM32F103xB)

# Link according to linker file.
add_executable(quetzal_elf)
target_link_options(quetzal_elf PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -T${LINKER_SCRIPT}
    -nostartfiles
    -Wl,-Map=quetzal.map,--cref
    -Wl,--print-memory-usage
    -Wl,--warn-common
    -Wl,--gc-sections
    # -Wl,--print-gc-sections
)
target_link_libraries(quetzal_elf quetzal_obj)

# Strip ELF information.
add_custom_command(
    TARGET quetzal_elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/quetzal_elf ${CMAKE_CURRENT_BINARY_DIR}/quetzal
)
