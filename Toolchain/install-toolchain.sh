#!/usr/bin/sh

# This script installs the toolchain for you

# Make sure user is in NakOS/Toolchain
CORRECT_DIR="*$NakOS/Toolchain/"

case $PWD/ in

  # Gets executed if we are in the the correct directory
  $CORRECT_DIR) 
  
    # Install the necessary dependencies
    sudo apt-get update && sudo apt-get install -y bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev

    # Create the necessary directories
    mkdir -p src opt/cross

    # Preparation for configuring binaries
    export PREFIX="$PWD/opt/cross"
    export TARGET=i686-elf
    export PATH="$PREFIX/bin:$PATH"

    # Configure, build, and install Binutils
    cd src
    git clone git://sourceware.org/git/binutils-gdb.git
    mkdir build-binutils
    cd build-binutils
    ../binutils-gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install
    
    # Configure, build, and install the GCC cross-compiler
    cd ..
    git clone git://gcc.gnu.org/git/gcc.git gcc
    mkdir build-gcc
    cd build-gcc
    ../gcc/configure --target=$TARGET -- prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
    make all-gcc
    make all-target-libgcc
    make all-target-libstdc++-v3
    make install-gcc
    make install-target-libstdc++-v3

    ;;

  # In the wrong directory
  *) 
    echo "You are in the wrong directory"
    echo "You must be in NakOS/Toolchain/ for the script to run correctly"
    ;;
esac

