//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_CGL_H
#define CELLULAR_AUTOMATA_CGL_H

#include "display.h"

class CGL {
public:
    /// We either init with an initial value to copy or nothing.
    CGL();
    explicit CGL(const std::vector<Node> &source);

    ~CGL() = default;

    /// Takes @times step's in Conway's Game of Life.
    /// \param times Number of steps to take
    void step(unsigned int times = 1);

    /// Copies @source to m_disp1 and sets m_curDisp to m_disp1
    /// \param source Vector to copy
    void initBoard(const std::vector<Node> &source);

private:

    /// Counts all of the neighbors of @X, @Y. Calls the m_lookX functions.
    /// \param x position
    /// \param y position
    /// \return Number of cells that are alive surrounding target
    unsigned int m_countNeighbors(unsigned int x, unsigned int y);

    // We define the grid around a cell as m_look1 -> m_look8 as such
    //      +-----+-----+-----+
    //      |  1  |  2  |  3  |
    //      +-----|-----|-----|
    //      |  4  |  T  |  5  |
    //      +-----+-----+-----+
    //      |  6  |  7  |  8  |
    //      +-----+-----+-----+
    // Where T is the target cell.

    /// Returns 0 if no alive cell is at location or 1 if it is alive.
    /// \param x position
    /// \param y position
    /// \return 1 or 0 if alive.
    bool m_look1(unsigned int x, unsigned int y);
    bool m_look2(unsigned int x, unsigned int y);
    bool m_look3(unsigned int x, unsigned int y);
    bool m_look4(unsigned int x, unsigned int y);
    bool m_look5(unsigned int x, unsigned int y);
    bool m_look6(unsigned int x, unsigned int y);
    bool m_look7(unsigned int x, unsigned int y);
    bool m_look8(unsigned int x, unsigned int y);

    /// Initializes the board
    void init();

    /// @m_disp1 and @m_disp2 are the 2 different boards. We need 2 since we
    /// read from 1 and write to another. If the write takes place before the
    /// read the cell's neighbors won't be counted correctly.
    std::vector<Node> m_disp1, m_disp2;

    /// Pointer to the current display. This should be read from for counting
    /// neighbors and posting to the Display class.
    std::vector<Node> *m_curDisp;

    /// Size of the board for convenience.
    unsigned int m_sizeX, m_sizeY;
};


#endif //CELLULAR_AUTOMATA_CGL_H
