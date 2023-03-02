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
class Graphics
{
  public:
    /* Hardware text mode color constants. */
    enum class VGA_Color : std::uint8_t {
        VGA_COLOR_BLACK = 0,
        VGA_COLOR_BLUE = 1,
        VGA_COLOR_GREEN = 2,
        VGA_COLOR_CYAN = 3,
        VGA_COLOR_RED = 4,
        VGA_COLOR_MAGENTA = 5,
        VGA_COLOR_BROWN = 6,
        VGA_COLOR_LIGHT_GREY = 7,
        VGA_COLOR_DARK_GREY = 8,
        VGA_COLOR_LIGHT_BLUE = 9,
        VGA_COLOR_LIGHT_GREEN = 10,
        VGA_COLOR_LIGHT_CYAN = 11,
        VGA_COLOR_LIGHT_RED = 12,
        VGA_COLOR_LIGHT_MAGENTA = 13,
        VGA_COLOR_LIGHT_BROWN = 14,
        VGA_COLOR_WHITE = 15
    };

  private:
    const std::size_t m_width  = 80;
    const std::size_t m_height = 25;

    std::uint8_t determine_color(VGA_Color foreground, VGA_Color background);

    /* Defines the full color */
    struct ColorCode
    {
        std::uint8_t color;
        explicit ColorCode(VGA_Color foreground, VGA_Color background);
        // Helper Method
        std::uint8_t determine_color(VGA_Color foreground, VGA_Color background);
    };
};


} // namespace Kernel
