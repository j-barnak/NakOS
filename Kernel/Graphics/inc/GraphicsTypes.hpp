#pragma once

#include <cstdint>
#include <cstddef>


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

/* Defines the full color */
struct ColorCode
{
    std::uint8_t color;
    ColorCode() = default;
    ColorCode(VGA_Color foreground, VGA_Color background);
    // Helper Method
    std::uint8_t determine_color(VGA_Color foreground, VGA_Color background);
};

/* Defines the actual characters */
struct ScreenChar
{
    std::uint8_t ascii_char;
    ColorCode color_code;
};

struct Writer
{
    std::size_t column_position;
    ColorCode   color_code;
};

template<std::size_t width, std::size_t height>
struct Buffer
{
    ScreenChar buffer[width][height];
};
