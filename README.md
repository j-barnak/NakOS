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
A `build/compile_commands.json` file will be created, but will not be using a standard library and additionally, we are in a freestanding environment. This means that
the compiler provides some header files. This also means that `clang` will probably not find these included files. To avoid this, add the cross-compiler location
to "directory" property like so:

```
[
    {
    "directory": /location/of/your/cross-compiler/
    }
]
```

