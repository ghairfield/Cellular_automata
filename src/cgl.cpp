//
// Created by g on 1/20/20.
//

#include "cgl.h"

CA::CGL::CGL(uint32_t maxX, uint32_t maxY, uint32_t spacing)
    : Unit(maxX, maxY, spacing)
{
}

std::vector<CA::Node>
CA::CGL::step(const std::vector<CA::Node> &board, uint32_t times)
{
    std::vector<CA::Node> newBoard(board);
    uint32_t neighbors = 0;

    for (uint32_t t = 0; t < 1; ++t)
    {
        for (uint32_t ix = 0; ix < unitsX(); ++ix)
        {
            for (uint32_t iy = 0; iy < unitsY(); ++iy)
            {
                neighbors = countNeighbors(board, ix, iy);
                // Conway's Game of Life rule set.
                if (board.at(xyToIndex(ix, iy)).val)
                {
                    // Cell is alive
                    if (neighbors < 2)
                    {
                        newBoard[xyToIndex(ix, iy)].val = 0;
                        newBoard[xyToIndex(ix, iy)].dirty = true;
                    }
                    else if (neighbors > 3)
                    {
                        newBoard[xyToIndex(ix, iy)].val = 0;
                        newBoard[xyToIndex(ix, iy)].dirty = true;
                    }
                }
                else
                {
                    if (neighbors == 3)
                    {
                        newBoard[xyToIndex(ix, iy)].val = 1;
                        newBoard[xyToIndex(ix, iy)].dirty = true;
                    }
                }
            }
        }
    }

    return newBoard;
}

uint32_t CA::CGL::countNeighbors(const std::vector<CA::Node> &board,
                                 uint32_t x, uint32_t y)
{
    uint32_t ret = 0;

    if (northWest(board, x, y))
        ++ret;
    if (north(board, x, y))
        ++ret;
    if (northEast(board, x, y))
        ++ret;
    if (west(board, x, y))
        ++ret;
    if (east(board, x, y))
        ++ret;
    if (southWest(board, x, y))
        ++ret;
    if (south(board, x, y))
        ++ret;
    if (southEast(board, x, y))
        ++ret;

    return ret;
}

inline bool CA::CGL::northWest(const std::vector<CA::Node> &board,
                               uint32_t x, uint32_t y) const
{
    if (y == 0 || x == 0)
        return false;
    else
        return board.at(xyToIndex(x - 1, y - 1)).val;
}

inline bool CA::CGL::north(const std::vector<CA::Node> &board,
                           uint32_t x, uint32_t y) const
{
    if (y == 0)
        return false;
    else
        return board.at(xyToIndex(x, y - 1)).val;
}

inline bool CA::CGL::northEast(const std::vector<CA::Node> &board,
                               uint32_t x, uint32_t y) const
{
    if (y == 0 || x >= unitsX() - 1)
        return false;
    else
        return board.at(xyToIndex(x + 1, y - 1)).val;
}

inline bool CA::CGL::west(const std::vector<CA::Node> &board,
                          uint32_t x, uint32_t y) const
{
    if (x == 0)
        return false;
    else
        return board.at(xyToIndex(x - 1, y)).val;
}

inline bool CA::CGL::east(const std::vector<CA::Node> &board,
                          uint32_t x, uint32_t y) const
{
    if (x >= unitsX() - 1)
        return false;
    else
        return board.at(xyToIndex(x + 1, y)).val;
}

inline bool CA::CGL::southWest(const std::vector<CA::Node> &board,
                               uint32_t x, uint32_t y) const
{
    if (y >= unitsY() - 1 || x == 0)
        return false;
    else
        return board.at(xyToIndex(x - 1, y + 1)).val;
}

inline bool CA::CGL::south(const std::vector<CA::Node> &board,
                           uint32_t x, uint32_t y) const
{
    if (y >= unitsY() - 1)
        return false;
    return board.at(xyToIndex(x, y + 1)).val;
}

inline bool CA::CGL::southEast(const std::vector<CA::Node> &board,
                               uint32_t x, uint32_t y) const
{
    if (y >= unitsY() - 1 || x >= unitsX() - 1)
        return false;
    else
        return board.at(xyToIndex(x + 1, y + 1)).val;
}