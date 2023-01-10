#pragma once

// Only a limited amount of headers are allowed
// becasuse we are in a Freestanding environment
// https://en.cppreference.com/w/cpp/freestanding
// #include <stdint.h>
#include <cstdint>
#include <cstddef>

namespace Kernel {

// VGA Text Mode
// Allows the ability to write to the terminal
class GraphicsDriver
{
  public:
    /* Hardware text mode color constants. */
    enum class VGA_Color {
        VGA_COLOR_BLACK,
        VGA_COLOR_BLUE,
        VGA_COLOR_GREEN,
        VGA_COLOR_CYAN,
        VGA_COLOR_RED,
        VGA_COLOR_MAGENTA,
        VGA_COLOR_BROWN,
        VGA_COLOR_LIGHT_GREY,
        VGA_COLOR_DARK_GREY,
        VGA_COLOR_LIGHT_BLUE,
        VGA_COLOR_LIGHT_GREEN,
        VGA_COLOR_LIGHT_CYAN,
        VGA_COLOR_LIGHT_RED,
        VGA_COLOR_LIGHT_MAGENTA,
        VGA_COLOR_LIGHT_BROWN,
        VGA_COLOR_WHITE,
    };

  private:
};

}// namespace Kernel
