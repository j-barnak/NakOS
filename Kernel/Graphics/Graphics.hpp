#pragma once

#include "Array.hpp"
#include "GraphicTypes.hpp"

class Graphics
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width = 80;

    std::size_t m_column_position;
    std::size_t m_row_position;

    using TerminalBuffer = Array<ScreenChar, m_height * m_width>;
    TerminalBuffer *m_buffer;

    void init_terminal();

  public:
    Graphics();
    ScreenChar get_character(std::uint8_t character, ColorCode color);
    ScreenChar get_character(std::uint8_t character);
    void write(const char *string);
};
