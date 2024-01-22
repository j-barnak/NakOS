#include "kernel.hpp"
#include "CPU/CPU.hpp"
#include "Graphics.hpp"

void kernel_main()
{
    auto gdtr = GDTR {};
    CPU::load_gtdr(gdtr);
    auto graphics = Graphics::Terminal {};
    char str[] = "frank0";
    graphics.write_string(str, 0, 0);
}
