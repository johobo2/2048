#include "grid.h"
#include "tile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

Grid::Grid(const int rows, const int cols, const int tileSize)
        : m_rows(rows), m_cols(cols), m_tileSize(tileSize)
{
    for(int row=0 ; row<rows ; ++row)
        for(int col=0 ; col<cols; ++col)
            m_tiles.push_back(Tile(row*tileSize, col*tileSize, tileSize, tileSize, 10.f));
            srand(time(NULL));
}
void Grid::draw(sf::RenderWindow& window)
{
    for(int row=0 ; row<m_rows ; ++row)
        for(int col=0 ; col<m_cols; ++col)
            setTile(row, col).drawTile(window);
}
const Tile& Grid::getTile(const int row, const int col) const
{
    return m_tiles[m_cols*row + col];
}
Tile& Grid::setTile(const int row, const int col)
{
    return m_tiles[m_cols*row + col];
}
void Grid::print() const
{
    for(int row=0 ; row<m_rows ; row++)
    {
        this->printRow(row);
        std::cout << '\n';
    }
    std::cout << '\n';
}
void Grid::printRow(const int row) const
{
    if(row < m_rows)
    {
        for(int col=0 ; col< m_cols ; col++)
            std::cout << this->getTile(row, col).getValue() << ' ';
    }
}
void Grid::printCol(const int col) const
{
    if(col < m_cols)
    {
        for(int row=0 ; row<m_rows ; ++row)
            std::cout << this->getTile(row, col).getValue() << '\n';
    }
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
            if(getTile(row, col).getValue() && row)
            {
                if(getTile(row - 1, col).getValue() == 0)
                {
                    newValue = getTile(row, col).getValue();
                    setTile(row -1, col).setValue(newValue);
                    setTile(row, col).setValue(0);
                    row -= 2;
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
        for(int row=0 ; row<m_rows-1 ; row++)
        {
            for(int col=row+1 ; col<m_cols ; col++)
            {
                temp = getTile(row, col).getValue();
                setTile(row, col).setValue(getTile(col, row).getValue());
                setTile(col, row).setValue(temp);
            }
        }
        //flip vertically
        for(int row=0 ; row<m_rows/2 ; row++)
        {
            for(int col=0 ; col<m_cols ; col++)
            {
                temp = getTile(row, col).getValue();
                setTile(row, col).setValue(getTile(m_rows - 1 - row, col).getValue());
                setTile(m_rows - 1 - row, col).setValue(temp);
            }
        }
        revolutions--;
    }
}

void Grid::combineUP()
{
    for(int row=0 ; row<m_rows-1 ; row++)
    {
        for(int col=0 ; col<m_cols ; col++)
        {
            if(getTile(row, col).getValue() && getTile(row, col).getValue() == getTile(row + 1, col).getValue())
            {
                setTile(row, col).setValue(getTile(row, col).getValue() * 2);
                setTile(row + 1, col).setValue(0);
            }
        }
    }
}
