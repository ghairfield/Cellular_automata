//
// Created by g on 1/20/20.
//

#include "display.h"

#define ARR_XY(x,y) ((x) + ((y) * (DISPLAY_MAX_X / DISPLAY_SPACING)))
#define MAX_ARR_X (DISPLAY_MAX_X / DISPLAY_SPACING)
#define MAX_ARR_Y (DISPLAY_MAX_Y / DISPLAY_SPACING)

Display::Display() : m_running(false), m_window(nullptr), m_render(nullptr)
{
    m_cell = new Node [DISPLAY_MAX_ARR];
    clearCells();
}

Display::~Display()
{
    delete [] m_cell;
}

bool Display::OnInit() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(DISPLAY_MAX_X, DISPLAY_MAX_Y, 0, &m_window, &m_render) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize the window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetWindowTitle(m_window, "Cellular Automation");
    m_running = true;

    return true;
}

bool Display::Run()
{
    if ( !m_running && !OnInit()) return false;
    SDL_Event event;

    while (m_running) {
        while (SDL_PollEvent(&event)) OnEvent(event);
        DisplayGridOnScreen();
        DrawScreen();
        SDL_RenderPresent(m_render);
        SDL_Delay(10);
    }

    return true;
}

void Display::DisplayGridOnScreen()
{
    SDL_SetRenderDrawColor(m_render, 3, 152, 252, SDL_ALPHA_OPAQUE);

    for (int ix = DISPLAY_SPACING; ix < DISPLAY_MAX_X; ix += DISPLAY_SPACING) {
        SDL_RenderDrawLine(m_render, ix, 0, ix, DISPLAY_MAX_Y);
    }
    for (int iy = DISPLAY_SPACING; iy < DISPLAY_MAX_Y; iy += DISPLAY_SPACING) {
        SDL_RenderDrawLine(m_render, 0, iy, DISPLAY_MAX_X, iy);
    }
}

void Display::DrawScreen() {
    SDL_Rect r;
    SDL_SetRenderDrawColor(m_render, 255, 11, 0, SDL_ALPHA_OPAQUE);

    for (int ix = 0; ix < MAX_ARR_X; ++ix) {
        for (int iy = 0; iy < MAX_ARR_Y; ++iy) {
            if (m_cell[ARR_XY(ix, iy)].val == 1 && m_cell[ARR_XY(ix, iy)].dirty) {
                r = {(ix * DISPLAY_SPACING + 2), (iy * DISPLAY_SPACING + 2), 7, 7};
                m_cell[ARR_XY(ix, iy)].dirty = false;
//                SDL_RenderFillRect(m_render, &r);
                if (SDL_RenderDrawRect(m_render, &r) != 0) {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not write rectangle to %d,%d", ix, iy);
                }
            }
        }
    }
}

void Display::OnDestroy() {
    if (m_render) SDL_DestroyRenderer(m_render);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Display::OnEvent(SDL_Event& e) {
    Event::OnEvent(e);
}

void Display::OnExit() {
    m_running = false;
}

 void Display::getCellPosition(std::pair<int, int> &pos, int x, int y) {
    pos.first = x / DISPLAY_SPACING;
    pos.second = y / DISPLAY_SPACING;
 }

void Display::OnLeftMouseDown(int x, int y) {
    std::pair<int, int> t;
    getCellPosition(t, x, y);
    writeCellPosition(t, 1);
}

void Display::OnMouseMoveWithLeftButton(int x, int y, int rx, int ry) {
    std::pair<int, int> t;
    getCellPosition(t, x, y);
    writeCellPosition(t, 1);
}

void Display::OnRightMouseDown(int x, int y) {
    std::pair<int, int> t;
    getCellPosition(t, x, y);
    writeCellPosition(t, 0);
}

void Display::OnMouseMoveWithRightButton(int x, int y, int rx, int ry) {
    std::pair<int, int> t;
    getCellPosition(t, x, y);
    writeCellPosition(t, 0);
}

void Display::clearCells() {
    for (int i = 0; i < DISPLAY_MAX_ARR; ++i) {
        m_cell[i].dirty = true;
        m_cell[i].val = 0;
    }
}

void Display::OnKeyDown(SDL_Scancode key, Uint16 mod) {
    if (key == SDL_SCANCODE_C) clearCells();
}

void Display::writeCellPosition(std::pair<int, int> &pos, char val) {
    int i = ARR_XY(pos.first, pos.second);
    m_cell[i].val = val;
    m_cell[i].dirty = true;
}
