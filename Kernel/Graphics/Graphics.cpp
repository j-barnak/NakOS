#include "Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<TerminalBuffer*>(0xb8000) }
{
}

void Graphics::init_terminal() 
{
    // Using 0 as a value because we are clearing the terminal
    auto initial_value = ScreenChar { 0, ColorCode { VGA_Color::White, VGA_Color::White } };

    for (std::uint16_t i = 0; i < m_row; ++i) {
        for (std::uint16_t j = 0; j < m_column; ++j) {
            *m_buffer[i][j] = initial_value;
        }
    }
}

ScreenChar Graphics::get_character(std::uint8_t character, ColorCode color)
{
    return  ScreenChar { character, color };
}

ScreenChar Graphics::get_character(std::uint8_t character)
{
    return  get_character(character, {} );
}
