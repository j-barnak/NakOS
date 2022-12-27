set(KERNEL_SOURCES
    ${CMAKE_SOURCE_DIR/Boot/boot.s} # Bootstrapped Assembly
    ${CMAKE_SOURCE_DIR/Kernel/src/kernel_main.cpp}
)

add_executable(nak ${KERNEL_SOURCES})

target_include_directories(nak PUBLIC ${CMAKE_SOURCE_DIR} )

target_compile_options(nak PRIVATE 
    $<$<CONFIG:Debug>:
    -fsanitize=address,leak,undefined -pedantic -Wall -Wextra -Wundef -Werror -Wno-unused-parameter
    >
)

target_link_options(nak PRIVATE 
    $<$<CONFIG:Debug>:
        -fsanitize=address,leak,undefined -T loader.ld # -T loader.ld specifies linker script
    >
)

target_compile_features(nak
    PRIVATE
        cxx_std_20
)

