#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Tile
{
private:
    const int m_x;
    const int m_y;
    const int m_width;
    const int m_height;
    const double m_borderThickness;
    sf::RectangleShape m_tile;
    sf::Text m_text;
    int m_value;

    static sf::Font s_font;

public:
    Tile(const int x, const int y, const int width, const int height, const double borderThickness);
    ~Tile() = default;

    void drawTile(sf::RenderWindow& window);

    void setValue(const int newValue);
    const int getValue() const;

    static bool loadFont(const char* path);
};

#endif // TILE_H_INCLUDED
