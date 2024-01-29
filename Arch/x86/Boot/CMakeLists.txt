set(BOOT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/boot.s
)

target_sources(nak PRIVATE ${BOOT_SOURCE})

