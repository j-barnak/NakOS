#pragma once

#include "CPU/CPU.hpp"

extern "C" {

void kernel_main();
void gdt_init(GDTR gdt_register);

}// extern "C"
