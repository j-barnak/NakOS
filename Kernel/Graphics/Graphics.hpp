#pragma once

#include "GraphicTypes.hpp"

class Graphics
{
  private:
    static constexpr std::uint8_t m_row = 25;
    static constexpr std::uint8_t m_column = 80;
    std::size_t m_column_position;

    using TerminalBuffer = ScreenChar[m_row][m_column];
    TerminalBuffer* m_buffer;

  public:
    Graphics();
    void init_terminal();
    ScreenChar get_character(std::uint8_t character, ColorCode color);
    ScreenChar get_character(std::uint8_t character);
};

