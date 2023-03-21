#include "inc/Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<TerminalBuffer*>(0xb8000) }
{
}

// TODO: Need to finish implementation
void Graphics::init_terminal() 
{

    auto c = get_character(static_cast<std::uint8_t>('a'), {});
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            *m_buffer[i][j] = c;
        }
    }
}

// TODO: Need to finish implementation
void Graphics::write_byte(std::uint8_t)
{

}

ScreenChar Graphics::get_character(std::uint8_t character, ColorCode color)
{
    return  ScreenChar { character, color };
}
