//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_CGL_H
#define CELLULAR_AUTOMATA_CGL_H

#include "display.h"

class CGL : public Display {
public:
    CGL();
    ~CGL();

    void step();

private:
// We define the grid around a cell as m_look1 -> m_look8 as such
//      +-----+-----+-----+
//      |  1  |  2  |  3  |
//      +-----|-----|-----|
//      |  4  |  T  |  5  |
//      +-----+-----+-----+
//      |  6  |  7  |  8  |
//      +-----+-----+-----+
//
// Where T is the target cell.

    unsigned int m_countNeighbors(unsigned int x, unsigned int y);

    bool m_look1(unsigned int x, unsigned int y);
    bool m_look2(unsigned int x, unsigned int y);
    bool m_look3(unsigned int x, unsigned int y);
    bool m_look4(unsigned int x, unsigned int y);
    bool m_look5(unsigned int x, unsigned int y);
    bool m_look6(unsigned int x, unsigned int y);
    bool m_look7(unsigned int x, unsigned int y);
    bool m_look8(unsigned int x, unsigned int y);

    char *m_disp1, *m_disp2, *m_curDisp;
    unsigned int m_sizeX, m_sizeY;
};


#endif //CELLULAR_AUTOMATA_CGL_H
