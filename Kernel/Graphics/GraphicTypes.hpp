#pragma once

#include <cstdint>

// Hardware text mode color constants.
enum class VGA_Color : std::uint8_t { Black = 0, Blue = 1, Green = 2, Cyan = 3, Red = 4, Magenta = 5, Brown = 6, Light_Grey = 7, Dark_Grey = 8, Light_Blue = 9, Light_Green = 10, Light_Cyan = 11, Light_Red = 12, Light_Magenta = 13, Light_Brown = 14, White = 15 };

// Defines the full color
#pragma pack(push, 1)
struct ColorCode
{
    std::uint8_t color;

    explicit ColorCode(VGA_Color foreground, VGA_Color background);
    ColorCode();

    std::uint8_t determine_color(VGA_Color foreground, VGA_Color background);
};
#pragma pack(pop)

// Defines the actual characters on VGA Screen
#pragma pack(push, 1)
struct ScreenChar
{
    std::uint8_t ascii_char;
    ColorCode color_code;

    // We are toggling the most signficant bit to a 1
    void enable_blinking()
    {
        ascii_char |= 0x80;
    }

    void disable_blinking()
    {
        ascii_char &= 0x7f;
    };
};
#pragma pack(pop)
