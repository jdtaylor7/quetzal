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
    -ffreestanding
    # -fstack-protector-strong
    -finline-small-functions
    -findirect-inlining
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
add_compile_definitions(STM32F103xB)

# Compile tests.
add_library(test_language_features OBJECT test/test_language_features.cpp)

# Compile object files.
add_library(clocks OBJECT src/clocks.cpp)
add_library(handlers OBJECT src/handlers.cpp)
add_library(serial OBJECT src/serial.cpp)
add_library(timers OBJECT src/timers.cpp)

# Compile quetzal executable.
add_library(${PROJECT_NAME}_lib OBJECT src/${PROJECT_NAME}.cpp)

# Compile vectors executable.
add_library(vectors_lib OBJECT src/vectors.cpp)

# Link executable according to linker file.
add_executable(${PROJECT_NAME}_elf)
target_link_libraries(${PROJECT_NAME}_elf
    vectors_lib
    ${PROJECT_NAME}_lib
    clocks
    handlers
    serial
    timers
    test_language_features
)

# Strip ELF information.
add_custom_command(
    TARGET ${PROJECT_NAME}_elf
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_elf ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
)
