#pragma once

// Only a limited amount of headers are allowed
// becasuse we are in a Freestanding environment
// https://en.cppreference.com/w/cpp/freestanding
#include "GraphicsTypes.hpp"


// We need to write to 0xb8000, so we should find the best way to write to 
// that address. We have to write to the buffer, so we need to set that address
// to where the IO is being performed. 
class Graphics
{
  private:
    static constexpr std::uint8_t m_row = 80;
    static constexpr std::uint8_t m_column = 25;
    std::size_t m_column_position;

    using TerminalBuffer = ScreenChar[m_row][m_column];
    TerminalBuffer* m_buffer;

  public:
    Graphics();
    void init_terminal();
    // TODO: Delete after testing
    void test_terminal();
    ScreenChar get_character(std::uint8_t character, ColorCode color);
    ScreenChar get_character(std::uint8_t character);
};

