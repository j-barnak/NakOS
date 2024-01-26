#pragma once

#include <cstdint>

namespace Graphics {

enum class Color : std::uint16_t {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    Pink = 13,
    Yellow = 14,
    White = 15,
};

struct ScreenCharacter
{
    Color background;
    Color foreground;
    unsigned char ascii;

    std::uint16_t to_16() const;
};

class Terminal
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width = 80;

    std::uint16_t *buffer;

    Color m_background;
    Color m_foreground;

    void initialize_terminal();

  public:
    void write_string(char str[], std::size_t x, std::size_t y);

  public:
    Terminal();
};

}// namespace Graphics
