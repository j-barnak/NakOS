# How to build the cross-compiler?

## Dependencies

You first need to install the dependencies. I will install using `aptitude`, but you may use `apt-get`. 

```
sudo aptitude update && aptitude install -y bison flex libgmp3-dev libmpc-dev libmpfr-dev \
texinfo libisl-dev
```

if you are using `apt-get`

```
sudo apt-get update && sudo apt-get install -y bison flex libgmp3-dev libmpc-dev libmpfr-dev \
texinfo libisl-dev
```

## Preparation and Installation

Create two folders from within `Toolchain` called `src` and `opt` and within `opt/`, create `cross`.
Your directory should look like:

```
Toolchain
├── src/
├── opt/
│   └── cross/
├── os-dev-toolchain.cmake
└── TOOLCHAIN.md
```

From within the `Toolchain` directory, run the following:

```
export PREFIX="$PWD/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

### Binutils

We need binutils because our cross-compiler needs to use tools configured correctly for our environment.

In `Toolchain/src`:

```
git clone git://sourceware.org/git/binutils-gdb.git
mkdir build-binutils
cd build-binutils
../binutils-gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
```

### GCC

And of course, you'll need a cross-compiler. So, in `Toolchain/src`

```
mkdir build-gcc
cd build-gcc
../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx
make all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libstdc++-v3
```

