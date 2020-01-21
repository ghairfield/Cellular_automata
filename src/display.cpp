//
// Created by g on 1/20/20.
//

#include "display.h"

Display::Display() : m_running(false), m_maxX(-1), m_maxY(-1), m_window(nullptr), m_render(nullptr), m_cells(nullptr)
{
}


bool Display::OnInit(int x, int y) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(x, y, 0, &m_window, &m_render) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize the window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    SDL_SetWindowTitle(m_window, "Cellular Automation");
    m_running = true;
    m_maxX = x;
    m_maxY = y;

    m_cells = new bool[x*y];

    return true;
}

bool Display::Run()
{
    if ( !m_running && !OnInit()) return false;
    SDL_Event event;

    while (m_running) {
        while (SDL_PollEvent(&event)) OnEvent(event);
        DrawGrid();

        SDL_RenderPresent(m_render);
    }

    return true;
}

void Display::DrawGrid(int spacing)
{
    SDL_SetRenderDrawColor(m_render, 3, 152, 252, SDL_ALPHA_OPAQUE);

    for (int ix = spacing; ix < m_maxX; ix += spacing) {
        SDL_RenderDrawLine(m_render, ix, 0, ix, m_maxY);
    }
    for (int iy = spacing; iy < m_maxY; iy += spacing) {
        SDL_RenderDrawLine(m_render, 0, iy, m_maxX, iy);
    }
}

void Display::OnDestroy() {
    if (m_render) SDL_DestroyRenderer(m_render);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();

    delete [] m_cells;
}

void Display::OnEvent(SDL_Event& e) {
    Event::OnEvent(e);
}

void Display::OnExit() {
    m_running = false;
}
