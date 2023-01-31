#pragma once

// Only a limited amount of headers are allowed
// becasuse we are in a Freestanding environment
// https://en.cppreference.com/w/cpp/freestanding
#include <cstdint>

namespace Kernel {

// VGA Text Mode
// Allows the ability to write to the terminal
// Based on: 
// https://os.phil-opp.com/vga-text-mode/
// https://wiki.osdev.org/Bare_Bones
class GraphicsDriver
{
  public:
    /* Hardware text mode color constants. */
    enum class VGA_Color {
        VGA_COLOR_BLACK         = 0,
        VGA_COLOR_BLUE          = 1,
        VGA_COLOR_GREEN         = 2,
        VGA_COLOR_CYAN          = 3,
        VGA_COLOR_RED           = 4,
        VGA_COLOR_MAGENTA       = 5,
        VGA_COLOR_BROWN         = 6,
        VGA_COLOR_LIGHT_GREY    = 7,
        VGA_COLOR_DARK_GREY     = 8,
        VGA_COLOR_LIGHT_BLUE    = 9,
        VGA_COLOR_LIGHT_GREEN   = 10,
        VGA_COLOR_LIGHT_CYAN    = 11,
        VGA_COLOR_LIGHT_RED     = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN   = 14,
        VGA_COLOR_WHITE         = 15
    };

  private:
    struct ColorCode 
    {

    };
    
};

} // namespace Kernel
