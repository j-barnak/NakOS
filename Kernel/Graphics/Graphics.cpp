#include "Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<TerminalBuffer*>(0xb8000) }
{
}

void Graphics::init_terminal() 
{
    // Zero Because we initialize terminal so that it's a white screen 
    auto initial_value = ScreenChar { 0 , ColorCode { VGA_Color::White, VGA_Color::Black } };

    for (std::size_t i = 0; i < m_row; ++i) {
        for (std::size_t j = 0; j < m_column; ++j) {
            (*m_buffer)[i][j] = initial_value;
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
