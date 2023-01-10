set(CMAKE_SYSROOT ${CMAKE_SOURCE_DIR}/Toolchain/)
set(CMAKE_C_COMPILER_WORKS 1)   # Skip Test because we are in a free-standing environment
set(CMAKE_CXX_COMPILER_WORKS 1) # Skip Test because we are in a free-standing environment
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/Toolchain/opt/cross/bin/i686-elf-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/Toolchain/opt/cross/bin/i686-elf-g++)
