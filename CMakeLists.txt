cmake_minimum_required(VERSION 3.20)
project(NakOS CXX ASM)

# Detect Architecture, Choose linker script based on architecture
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Toolchain/loader.ld)

add_executable(nak)

add_subdirectory(Arch/x86)
add_subdirectory(Kernel)
add_subdirectory(Kernel/Graphics)
add_subdirectory(Lib)

target_include_directories(nak PUBLIC ${CMAKE_SOURCE_DIR})

target_compile_options(nak PUBLIC 
    $<$<CONFIG:Debug>:
    -pedantic 
    -Wall 
    -Wextra 
    -Wundef 
    -Werror 
    -ffreestanding 
    -fno-exceptions 
    -fno-rtti 
    -ggdb
    -O0
    -g3
    -Wno-unused 
    -Wno-unused-parameter
    >
)

target_link_options(nak PUBLIC 
     -ffreestanding -nostdlib LINKER:-T${LINKER_SCRIPT}
)

set_target_properties(nak PROPERTIES 
    LINK_DEPENDS ${LINKER_SCRIPT}
    CXX_STANDARD 20
)
