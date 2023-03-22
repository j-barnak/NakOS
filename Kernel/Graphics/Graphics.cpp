#include "Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<TerminalBuffer*>(0xb8000) }
{
}

void Graphics::init_terminal() 
{
    auto initial_value = ScreenChar { static_cast<std::uint8_t>('a'), ColorCode { VGA_Color::White, VGA_Color::Black } };

    for (std::size_t i = 0; i < m_row; ++i) {
        for (std::size_t j = 0; j < m_column; ++j) {
            *m_buffer[i][j] = initial_value;
            ++initial_value.ascii_char;
            ++m_column_position; 
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
