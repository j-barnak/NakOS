# NakOS

NakOS is an operating system written using C++.

## Developing for NakOS

To develop for NakOS, you must first set up your cross-compiler. Instructions on how to do this could be found [here](https://wiki.osdev.org/GCC_Cross-Compiler#Why_cross-compilers_are_necessary). Put the 
cross compiler in folder called `Toolchain/`.

## Building NakOS

```
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=1 . -GNinja -DCMAKE_TOOLCHAIN_FILE=Toolchain/os-dev-toolchain.cmake
```

## Misc.

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
