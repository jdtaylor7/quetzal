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

# Add compile/link options.
add_compile_options(
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
add_link_options(
    -mcpu=cortex-m3
    -mthumb
    -T${LINKER_SCRIPT}
    -nostartfiles
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--print-memory-usage
    -Wl,--warn-common
    -Wl,--gc-sections
    # -Wl,--print-gc-sections
    -Wl,--orphan-handling=error
)

# Compile executable as an object file.
add_library(${PROJECT_NAME}_obj OBJECT src/${PROJECT_NAME}.cpp)
target_compile_definitions(${PROJECT_NAME}_obj PRIVATE -DSTM32F103xB)

# Link executable according to linker file.
add_executable(${PROJECT_NAME}_elf)
target_link_libraries(${PROJECT_NAME}_elf
    ${PROJECT_NAME}_obj
)

# Strip ELF information.
add_custom_command(
    TARGET ${PROJECT_NAME}_elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_elf ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)
