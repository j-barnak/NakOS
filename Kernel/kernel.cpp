#include "kernel.hpp"
#include "Graphics.hpp"
#include "Processor/GDT.hpp"

void kernel_main()
{
    auto gdtr = Processor::GDTR { .base = 0, .limit = 0xFFFF };
    auto gdt = Processor::GDT { gdtr };
    gdt.load_gtdr();

    auto graphics = Graphics::Terminal {};
    char str[] = "Loaded GDT";
    graphics.write_string(str, 0, 0);
}
