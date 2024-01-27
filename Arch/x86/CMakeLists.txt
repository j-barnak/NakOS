set(GRAPHICS_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/GDT.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor.cpp
)

target_include_directories(nak PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(nak PRIVATE ${GRAPHICS_SOURCE})

