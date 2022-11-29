cmake_minimum_required(VERSION 3.20)
project(NakOS)

add_executable(nak ${SOURCES})

target_include_directories(nak PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options( nak PRIVATE 
    $<$<CONFIG:Debug>:
    -fsanitize=address,leak -pedantic -Wall -Wextra -Wundef -Werror 
    >
)

target_link_options( nak PRIVATE 
    $<$<CONFIG:Debug>:
        -fsanitize=address,leak
    >
)

target_compile_features( nak
    PRIVATE
        cxx_std_20
)
