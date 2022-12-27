cmake_minimum_required(VERSION 3.20)
project(NakOS C CXX ASM)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Kernel/Boot/loader.ld)

add_executable(nak)

add_subdirectory(Kernel)

target_include_directories(nak PUBLIC ${CMAKE_SOURCE_DIR})

target_compile_options(nak PUBLIC 
    $<$<CONFIG:Debug>:
     -pedantic -Wall -Wextra -Wundef -Werror -Wno-unused-parameter -ffreestanding -fno-exceptions -fno-rtti -m32
    >
)

target_link_options(nak PUBLIC 
    $<$<CONFIG:Debug>:
     -ffreestanding -nostdlib -T${LINKER_SCRIPT}
    >
)

target_compile_features(nak
    PUBLIC
        cxx_std_20
)
