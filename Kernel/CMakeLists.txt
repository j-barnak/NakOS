set(KERNEL_SOURCE
    ${CMAKE_SOURCE_DIR}/Kernel/Boot/boot.s
    ${CMAKE_SOURCE_DIR}/Kernel/kernel.cpp
)

target_include_directories(nak PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(nak PRIVATE ${KERNEL_SOURCE})
