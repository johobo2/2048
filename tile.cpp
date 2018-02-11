#include "tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

sf::Font Tile::s_font;

Tile::Tile(const int x, const int y, const int width, const int height, const double borderThickness)
    : m_x(x + borderThickness/2), m_y(y + borderThickness/2), m_width(width - borderThickness), m_height(height - borderThickness), m_borderThickness(borderThickness), m_tile(sf::Vector2f(m_height, m_width)), m_value(0)
{
    m_tile.setPosition(m_y, m_x);
    m_tile.setOutlineColor(sf::Color(60, 60, 60));
    m_tile.setOutlineThickness(m_borderThickness);

    m_text.setFont(s_font);
    m_text.setCharacterSize(48);
}

void Tile::setValue(const int newValue)
{
    m_value = newValue;
}

const int Tile::getValue() const
{
    return m_value;
}

void Tile::drawTile(sf::RenderWindow& window)
{
    int val = m_value;
    int transparency = 0;
    while(val > 1)
    {
        val /= 2;
        transparency++;
    }
    m_tile.setFillColor(sf::Color(255, 255, 0, transparency * 255 / 11));
    window.draw(m_tile);

    m_text.setString(std::to_string(m_value));
    m_text.setPosition(m_y + m_width / 2.f - m_text.getLocalBounds().width / 2.f, m_x + m_height / 2.f - m_text.getLocalBounds().height);
    if(m_value)
        window.draw(m_text);
}

bool Tile::loadFont(const char* path)
{
    return s_font.loadFromFile(path);
}
