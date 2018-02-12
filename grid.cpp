#include "grid.h"
#include "tile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

Grid::Grid(const int cols, const int rows, const int tileSize)
        : m_cols(cols), m_rows(rows), m_tileSize(tileSize)
{
    for(int col=0 ; col<cols ; col++)
        for(int row=0 ; row<rows; row++)
            m_tiles.push_back(Tile(col*tileSize, row*tileSize, tileSize, tileSize, 10.f));
            srand(time(NULL));
}
void Grid::draw(sf::RenderWindow& window)
{
    for(int col=0 ; col<m_cols ; col++)
        for(int row=0 ; row<m_rows; row++)
            setTile(col, row).drawTile(window);
}
const Tile& Grid::getTile(const int col, const int row) const
{
    return m_tiles[m_rows*col + row];
}
Tile& Grid::setTile(const int col, const int row)
{
    return m_tiles[m_rows*col + row];
}
void Grid::spawnTile()
{
    int index;
    while(1)
    {
        index = rand() % (m_cols * m_rows);
        if(m_tiles[index].getValue() == 0)
        {
            double random = static_cast<double>(rand()) / RAND_MAX;
            int newValue = random < 0.9 ? 2 : 4;
            m_tiles[index].setValue(newValue);
            return;
        }
    }
}
void Grid::slideUP()
{
    int newValue;
    for(int col=0 ; col<m_cols ; col++)
    {
        for(int row=0 ; row<m_rows ; row++)
        {
            if(getTile(col, row).getValue() && col)
            {
                if(getTile(col - 1, row).getValue() == 0)
                {
                    newValue = getTile(col, row).getValue();
                    setTile(col -1, row).setValue(newValue);
                    setTile(col, row).setValue(0);
                    col -= 2;
                }
            }
        }
    }
}

void Grid::slideAndMerge(const int direction)
{
    rotateGrid(direction);
    slideUP();
    combineUP();
    slideUP();
    rotateGrid((4 - direction) % 4);
}

void Grid::rotateGrid(int revolutions)
{
    int temp;
    while(revolutions)
    {
        //flip diagonally
        for(int col=0 ; col<m_cols-1 ; col++)
        {
            for(int row=col+1 ; row<m_rows ; row++)
            {
                temp = getTile(col, row).getValue();
                setTile(col, row).setValue(getTile(row, col).getValue());
                setTile(row, col).setValue(temp);
            }
        }
        //flip vertically
        for(int col=0 ; col<m_cols/2 ; col++)
        {
            for(int row=0 ; row<m_rows ; row++)
            {
                temp = getTile(col, row).getValue();
                setTile(col, row).setValue(getTile(m_cols - 1 - col, row).getValue());
                setTile(m_cols - 1 - col, row).setValue(temp);
            }
        }
        revolutions--;
    }
}

void Grid::combineUP()
{
    for(int col=0 ; col<m_cols-1 ; col++)
    {
        for(int row=0 ; row<m_rows ; row++)
        {
            if(getTile(col, row).getValue() && getTile(col, row).getValue() == getTile(col + 1, row).getValue())
            {
                setTile(col, row).setValue(getTile(col, row).getValue() * 2);
                setTile(col + 1, row).setValue(0);
            }
        }
    }
}
