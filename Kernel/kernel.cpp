#include "kernel.hpp"
#include "Graphics.hpp"
#include "Processor/GDT.hpp"

void kernel_main()
{
    auto gdtr = Processor::GDTR {};
    auto gdt = Processor::GDT {};
    gdt.load_gtdr(gdtr);
    auto graphics = Graphics::Terminal {};
    char str[] = "frank0";
    graphics.write_string(str, 0, 0);
}
