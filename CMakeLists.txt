cmake_minimum_required(VERSION 3.20)
project(NakOS C CXX ASM)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Kernel/Boot/loader.ld)

add_executable(nak)

add_subdirectory(Kernel)

target_include_directories(nak PUBLIC ${CMAKE_SOURCE_DIR})

target_compile_options(nak PUBLIC 
    $<$<CONFIG:Debug>:
    -fsanitize=address,leak,undefined -pedantic -Wall -Wextra -Wundef -Werror -Wno-unused-parameter -ffreestanding -fno-exceptions -fno-rtti
    >
)

target_link_options(nak PUBLIC 
    $<$<CONFIG:Debug>:
        -fsanitize=address,leak,undefined -ffreestanding -nostdlib
    >
)

target_compile_features(nak
    PUBLIC
        cxx_std_20
)

set_target_properties(nak PROPERTIES 
    LINKER_LANGUAGE CXX
    LINK_DEPENDS ${LINKER_SCRIPT}
)
