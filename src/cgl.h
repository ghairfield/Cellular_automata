//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_CGL_H
#define CELLULAR_AUTOMATA_CGL_H

#include <utility>
#include "display.h"
#include "node.h"
#include "unit.h"

namespace CA
{

    class CGL : public Unit
    {
    public:
        CGL() = delete;

        /**
         * @brief Construct a new CGL object
         *
         * @param maxX Size in pixels of width
         * @param maxY size in pixels of height
         * @param spacing Square pixel that makes up each cell
         */
        CGL(uint32_t maxX, uint32_t maxY, uint32_t spacing);

        ~CGL() = default;

        /**
         * @brief Operates on `board` and takes `times` steps in the game.
         *
         * @param board A board of Nodes to run Conway's game of life
         * @param times Number of *lives* to take (currently unimplemented)
         * @return std::vector<Node>&&
         */
        std::vector<Node>
        step(const std::vector<Node> &board, uint32_t times = 1);

    private:
        /// Counts all of the neighbors of @X, @Y. Calls the m_lookX functions.
        /// \param x position
        /// \param y position
        /// \return Number of cells that are alive surrounding target

        /**
         * @brief Returns the count of all cells active around the cell
         * at `unit` x, y.
         *
         * @param board Grid of cells
         * @param x `Unit` X position of target
         * @param y `Unit` Y position of target
         * @return uint32_t Number of 'alive' cells surrounding target
         */
        uint32_t countNeighbors(const std::vector<Node> &board,
                                uint32_t x, uint32_t y);

        // We define the grid around a cell as
        //      +-----+-----+-------+
        //      |  NW  |  N  |  NE  |
        //      +------|-----|------|
        //      |  W   |  T  |  E   |
        //      +------+-----+------+
        //      |  SW  |  S  |  SE  |
        //      +-----+-----+-------+
        // Where T is the target cell.

        /**
         * @brief Counts an individual cell from a target of x,y
         *
         * @param board Grid of cells
         * @param x Target X
         * @param y Target Y
         * @return true If target neighbor is 'alive'
         * @return false If target neighbor is 'dead'
         */
        bool northWest(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool north(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool northEast(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool west(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool east(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool southWest(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool south(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
        bool southEast(const std::vector<Node> &board, uint32_t x, uint32_t y) const;
    };

} /* namespace CA */
#endif /* CELLULAR_AUTOMATA_CGL_H */
