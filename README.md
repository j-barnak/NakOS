# NakOS

NakOS is an operating system written using C++.

## Developing for NakOS

To develop for NakOS, you must first set up your cross-compiler. Instructions on how to do this could be found [here](https://wiki.osdev.org/GCC_Cross-Compiler#Why_cross-compilers_are_necessary). Put the 
cross compiler in folder called `Toolchain/`.

The way you configure and build gcc should be slightly modified when you work with C++. The guide will only correctly configure the freestanding libc libraries, but we want libstd++, gcc's version of C++
Standard Library. You instead build `libc` *and* `libstd++` like so:

```
mkdir build-gcc
cd build-gcc
# '--disable-hosted-libstdcxx' is added
../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
# Need to add for freestanding C++ Standard Libraries
make all-target-libstdc++-v3
make install-gcc
# Need to add for freestanding C++ Standard Libraries
make install-target-libstdc++-v3
```
make install-target-libgcc

## Building NakOS

```
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . -GNinja -DCMAKE_TOOLCHAIN_FILE=Toolchain/os-dev-toolchain.cmake
```

## Misc.

### LSP Setup

If you're using `clangd`, you have to pass `--query-driver=/path/to/cross-compiler` as an argument. I use Conquer of Completion, better known simply as CoC. In my CoC config file (you reach
this file with `:CocConfig`) within vim.  The file should look like:

    {
        "clangd.arguments": ["--query-driver=/home/jared/projects/cpp_projects/NakOS/Toolchain/opt/cross/bin/i686-elf-g++"]
    }

You may have more properties within the configuration file and the path to the cross-compiler  will certainly differ.



