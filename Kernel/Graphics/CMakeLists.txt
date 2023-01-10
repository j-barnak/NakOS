set(GRAPHICS_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics.cpp
)

target_sources(nak PUBLIC ${GRAPHICS_SOURCE})

target_include_directories(nak PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
