#include "inc/Graphics.hpp"

Graphics::Graphics()
    : m_column_position { 0 },
      m_buffer { reinterpret_cast<Buffer<m_width, m_height>*>(0xb8000) },
      m_color_code {}
{
    
}

// TODO: Need to finish implementation
void Graphics::init_terminal() 
{
    auto initial_color = VGA_Color::Green;
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j) {
        }
    }
}
