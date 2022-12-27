set(KERNEL_SOURCE
    ${CMAKE_SOURCE_DIR}/Kernel/Boot/boot.s
    ${CMAKE_SOURCE_DIR}/Kernel/src/kernel.cpp
)

target_sources(nak PRIVATE ${KERNEL_SOURCE})
