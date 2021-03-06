set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

set(TOOLCHAIN_PREFIX "arm-none-eabi")

# Get toolchain directory
find_program(GCC_FULL_PATH ${TOOLCHAIN_PREFIX}-gcc)
if (NOT GCC_FULL_PATH)
    message(FATAL_ERROR "Cross compiler ${TOOLCHAIN_PREFIX}-gcc not found")
endif()
get_filename_component(TOOLCHAIN_DIR ${GCC_FULL_PATH} PATH)

# Set compilers.
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_C_COMPILER ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-g++)

# Set other binutils.
set(CMAKE_LINKER ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-ld)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-as)
set(CMAKE_OBJCOPY ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-objcopy)
set(CMAKE_STRIP ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-strip)
set(CMAKE_CPP ${TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}-cpp)
