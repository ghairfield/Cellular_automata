//
// Created by g on 1/20/20.
//

#include "display.h"

Display::Display() : m_running(false), m_window(nullptr), m_render(nullptr)
{
    m_cell = new char [DISPLAY_MAX_X * DISPLAY_MAX_Y];
    for (int i = 0; i < DISPLAY_MAX_X * DISPLAY_MAX_Y; ++i)
        m_cell[i] = 0;
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
        SDL_Delay(100);
    }

    return true;
}

void Display::DisplayGridOnScreen()
{
    SDL_SetRenderDrawColor(m_render, 3, 152, 252, SDL_ALPHA_OPAQUE);

    for (int ix = spacing; ix < DISPLAY_MAX_X; ix += spacing) {
        SDL_RenderDrawLine(m_render, ix, 0, ix, DISPLAY_MAX_Y);
    }
    for (int iy = spacing; iy < DISPLAY_MAX_Y; iy += spacing) {
        SDL_RenderDrawLine(m_render, 0, iy, DISPLAY_MAX_X, iy);
    }
}

void Display::DrawScreen()
{
    SDL_SetRenderDrawColor(m_render, 255, 111, 0, SDL_ALPHA_OPAQUE);

    for (int x = 0; x < DISPLAY_MAX_X; ++x) {
        for (int y = 0; y < DISPLAY_MAX_Y; ++y) {
           if (m_cell[x + (y * DISPLAY_MAX_Y)] == 1) {
               SDL_Rect r = { (x * spacing + 2), (y * spacing + 2), 7, 7};
               SDL_RenderFillRect(m_render, &r);
               if (SDL_RenderDrawRect(m_render, &r) != 0) {
                   SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not write rectangle to %d,%d", (x * spacing + 1), (y * spacing + 1));
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
    pos.first = x / spacing;
    pos.second = y / spacing;
}

void Display::OnLeftMouseDown(int x, int y) {
    std::pair<int, int> t;
    getCellPosition(t, x, y);

    m_cell[t.first + (t.second * DISPLAY_MAX_Y)] = 1;
}

void Display::OnMouseMoveWithLeftButton(int x, int y, int rx, int ry) {
    Event::OnMouseMoveWithLeftButton(x, y, rx, ry);
}

void Display::OnLeftMouseUp(int x, int y) {
    Event::OnLeftMouseUp(x, y);
}
