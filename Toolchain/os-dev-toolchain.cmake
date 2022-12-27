set(CMAKE_C_COMPILER_WORKS 1)   # Skip Test for Cross Compilation
set(CMAKE_CXX_COMPILER_WORKS 1) # Skip Test for Cross Compilation
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/Toolchain/opt/cross/bin/i686-elf-g++)
