#pragma once

#include "GraphicTypes.hpp"
#include "Array.hpp"

class Graphics
{
  private:
    static constexpr std::uint8_t m_height = 25;
    static constexpr std::uint8_t m_width  = 80;
    std::size_t m_column_position;

    using TerminalBuffer = Array<ScreenChar, m_height * m_width>;
    TerminalBuffer* m_buffer;

  public:
    Graphics();
    void init_terminal();
    // TODO: Implement
    void enable_blinking();
    ScreenChar get_character(std::uint8_t character, ColorCode color);
    ScreenChar get_character(std::uint8_t character);
};

