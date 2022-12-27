set(KERNEL_SOURCE
    ${CMAKE_SOURCE_DIR/Boot/boot.s} 
    ${CMAKE_SOURCE_DIR/Kernel/src/kernel_main.cpp}
)

target_sources(nak PUBLIC ${CMAKE_SOURCE_DIR}
