#include "Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<TerminalBuffer*>(0xb8000) }
{
}

// TODO: Need to finish implementation
void Graphics::init_terminal() 
{
    char c = 'a';
    auto vga_char = get_character(static_cast<std::uint8_t>(c));

    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
            *m_buffer[i][j] = vga_char;
            c++;
            vga_char = get_character(static_cast<std::uint8_t>(c));
        }
    }
}

constexpr ScreenChar Graphics::get_character(std::uint8_t character, ColorCode color)
{
    return  ScreenChar { character, color };
}

constexpr ScreenChar Graphics::get_character(std::uint8_t character)
{
    return  get_character(character, {} );
}
