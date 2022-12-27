# NakOS

NakOS is an operating system written using C++.

## Developing for NakOS

To develop for NakOS, you must first set up your cross-compiler. Instructions on how to do this could be found [here](https://wiki.osdev.org/GCC_Cross-Compiler#Why_cross-compilers_are_necessary). Put the 
cross compiler in folder called `Toolchain/`.

## Building NakOS

cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . -GNinja -DCMAKE_TOOLCHAIN_FILE=Toolchain/os-dev-toolchain.cmake

