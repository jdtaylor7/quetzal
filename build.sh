#!/bin/sh

# Exit if any command fails.
set -e

while getopts "re:h" flag
do
    case $flag in
    r) r_flag=1 ;;
    e) e_flag=1
       e_val="$OPTARG" ;;
    h | ?) echo "Usage: $0: [-r][-t target]"
           echo "   -r: Rebuild build directory"
           echo "   -e: Specify build executable"
           exit 2;;
    esac
done

if [ ! -z "$r_flag" ]; then
    echo "Rebuilding build directory"
    rm -rf ./build
fi
mkdir -p build
cd build

cmake -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-arm-none-eabi.cmake ..

# Add cmake build command line variables.
build_flags=""
if [ ! -z "$e_flag" ]; then
    echo "Building target $e_val"
    build_flags="$build_flags --target $e_val"
else
    echo "Building all targets"
fi

cmake --build . $build_flags -- VERBOSE=1
