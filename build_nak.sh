#/bin/bash

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Use the cross compiler
export CXX="$HOME/opt/cross/bin/$TARGET-gcc"

# Generate the files in the build/ directory
# cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . -GNinja
