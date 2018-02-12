#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.h"
#include "grid.h"

int main()
{
    const int cols = 4;
    const int rows = 4;
    const int tileSize = 100;

    Tile::loadFont("resources/sansation.ttf");

    sf::RenderWindow window(sf::VideoMode(rows*tileSize, cols*tileSize), "2048", sf::Style::Titlebar | sf::Style::Close);
    sf::Color backgroundColor(125, 125, 125);

    Grid gameGrid(cols, rows, tileSize);
    gameGrid.spawnTile();
    gameGrid.spawnTile();

    //gameGrid.print();
    window.clear(backgroundColor);
    gameGrid.draw(window);
    window.display();

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                case sf::Keyboard::Up:
                    gameGrid.slideAndMerge(0);
                    gameGrid.spawnTile();
                    window.clear(backgroundColor);
                    gameGrid.draw(window);
                    window.display();
                    //gameGrid.print();
                    break;
                case sf::Keyboard::Right:
                    gameGrid.slideAndMerge(1);
                    gameGrid.spawnTile();
                    window.clear(backgroundColor);
                    gameGrid.draw(window);
                    window.display();
                    //gameGrid.print();
                    break;
                case sf::Keyboard::Down:
                    gameGrid.slideAndMerge(2);
                    gameGrid.spawnTile();
                    window.clear(backgroundColor);
                    gameGrid.draw(window);
                    window.display();
                    //gameGrid.print();
                    break;
                case sf::Keyboard::Left:
                    gameGrid.slideAndMerge(3);
                    gameGrid.spawnTile();
                    window.clear(backgroundColor);
                    gameGrid.draw(window);
                    window.display();
                    //gameGrid.print();
                    break;
                default:;
                }
            }
        }
    }

    return 0;
}
