set(KERNEL_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR/kernel.cpp}
)

target_include_directories(nak PUBLIC ${CMAKE_SOURCE_DIR} )

target_compile_options(nak PRIVATE 
    $<$<CONFIG:Debug>:
    -fsanitize=address,leak,undefined -pedantic -Wall -Wextra -Wundef -Werror 
    >
)

target_link_options(nak PRIVATE 
    $<$<CONFIG:Debug>:
        -fsanitize=address,leak,undefined
    >
)

target_compile_features(nak
    PRIVATE
        cxx_std_20
)
