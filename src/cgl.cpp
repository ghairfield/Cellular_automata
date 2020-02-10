//
// Created by g on 1/20/20.
//

#include "cgl.h"

CGL::CGL() : m_curDisp(nullptr) {

    m_disp1.reserve((DISPLAY_MAX_ARR));
    m_disp2.reserve((DISPLAY_MAX_ARR));

    init();
    m_sizeX = DISPLAY_MAX_X / DISPLAY_SPACING;
    m_sizeY = DISPLAY_MAX_Y / DISPLAY_SPACING;
}

CGL::CGL(const std::vector<Node> &source) : m_curDisp(nullptr) {
    m_disp1.reserve((DISPLAY_MAX_ARR));
    m_disp2.reserve((DISPLAY_MAX_ARR));
    init();
    m_sizeX = DISPLAY_MAX_X / DISPLAY_SPACING;
    m_sizeY = DISPLAY_MAX_Y / DISPLAY_SPACING;
    initBoard(source);
}

void CGL::step(unsigned int times) {

    unsigned int neighbors = 0;
    std::vector<Node> &nextbuf = (m_curDisp == &m_disp1) ? m_disp2 : m_disp1;

    for (unsigned int t = 0; t < times; ++t) {
        for (unsigned int ix = 0; ix < DISPLAY_MAX_X; ++ix) {
            for (unsigned int iy = 0; iy < DISPLAY_MAX_Y; ++iy) {
                neighbors = m_countNeighbors(ix, iy);
                // Conway's Game of Life rule set.
                if (m_curDisp->at(ARR_XY(ix, iy)).val != 0) {
                    // Cell is alive
                    if (neighbors < 2) {
                        nextbuf[ARR_XY(ix, iy)].val = 0;
                        nextbuf[ARR_XY(ix, iy)].dirty = true;
                    } else if (neighbors > 3) {
                        nextbuf[ARR_XY(ix, iy)].val = 0;
                        nextbuf[ARR_XY(ix, iy)].dirty = true;

                    }
                } else {
                    if (neighbors == 3) {
                        nextbuf[ARR_XY(ix, iy)].val = 1;
                        nextbuf[ARR_XY(ix, iy)].dirty = true;

                    }
                }
            }
        }
    }
}

void CGL::initBoard(const std::vector<Node> &source) {
    if ( !m_disp1.empty()) m_disp1.clear();
    for (auto i : source) {
        m_disp1.push_back(i);
    }
    m_curDisp = &m_disp1;
}

unsigned int CGL::m_countNeighbors(unsigned int x, unsigned int y) {
    unsigned int ret = 0;

    if (m_look1(x, y)) ++ret;
    if (m_look2(x, y)) ++ret;
    if (m_look3(x, y)) ++ret;
    if (m_look4(x, y)) ++ret;
    if (m_look5(x, y)) ++ret;
    if (m_look6(x, y)) ++ret;
    if (m_look7(x, y)) ++ret;
    if (m_look8(x, y)) ++ret;

    return ret;
}

bool CGL::m_look1(unsigned int x, unsigned int y) {
    if (y == 0 || x == 0) return false;
    else return m_curDisp->at(ARR_XY(x - 1, y - 1)).val;
}

bool CGL::m_look2(unsigned int x, unsigned int y) {
    if (y == 0) return false;
    else return m_curDisp->at(ARR_XY(x, y - 1)).val;
}

bool CGL::m_look3(unsigned int x, unsigned int y) {
    if (y == 0 || x >= MAX_ARR_X - 1) return false;
    else return m_curDisp->at(ARR_XY(x + 1, y - 1)).val;
}

bool CGL::m_look4(unsigned int x, unsigned int y) {
    if (x == 0) return false;
    else return m_curDisp->at(ARR_XY(x - 1, y)).val;
}

bool CGL::m_look5(unsigned int x, unsigned int y) {
    if (x >= MAX_ARR_X - 1) return false;
    else return m_curDisp->at(ARR_XY(x + 1, y)).val;
}

bool CGL::m_look6(unsigned int x, unsigned int y) {
    if ( y >= MAX_ARR_Y - 1 || x == 0) return false;
    else return m_curDisp->at(ARR_XY(x - 1, y + 1)).val;
}

bool CGL::m_look7(unsigned int x, unsigned int y) {
    if ( y >= MAX_ARR_Y - 1) return false;
    return m_curDisp->at(ARR_XY(x, y + 1)).val;
}

bool CGL::m_look8(unsigned int x, unsigned int y) {
    if ( y >= MAX_ARR_Y - 1 || x >= MAX_ARR_X - 1) return false;
    else return m_curDisp->at(ARR_XY(x + 1, y + 1)).val;
}

void CGL::init() {
    for (int i = 0; i < DISPLAY_MAX_ARR; ++i) {
        m_disp1.push_back( {0, false} );
        m_disp2.push_back( {0, false} );
    }

    m_curDisp = &m_disp1;
}
