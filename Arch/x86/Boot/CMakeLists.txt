set(BOOT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/boot.s
)

target_include_directories(nak PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(nak PRIVATE ${PROCESSOR_SOURCE})

