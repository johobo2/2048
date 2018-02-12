#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <vector>

namespace sf
{
    class RenderWindow;
}
class Tile;

class Grid
{
private:
    const int m_cols;
    const int m_rows;
    const int m_tileSize;
    std::vector<Tile> m_tiles;

    Tile& setTile(const int cols, const int rows);
    void slideUP();
    void combineUP();
    void rotateGrid(int revolutions);

public:
    Grid(const int cols, const int rows, const int tileSize);
    ~Grid() = default;

    void draw(sf::RenderWindow& window);

    void spawnTile(); //dumb name. rename
    void slideAndMerge(const int direction);

    const Tile& getTile(const int col, const int row) const;

};

#endif // GRID_H_INCLUDED
