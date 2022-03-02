//
// Created by g on 1/20/20.
//

#include <iostream> // std::cerr
#include "display.h"

CA::Display::Display(uint32_t maxX, uint32_t maxY, uint32_t spacing)
    : m_window(nullptr), m_render(nullptr), m_displayGrid(false),
      Unit(maxX, maxY, spacing)
{
}

CA::Display::~Display()
{
    // Confirm that destroy was called
    if (m_window)
    {
        std::cerr << "destroy not called! Window was not cleaned up!!\n";
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Window not destroyed!");
    }
    if (m_render)
    {
        std::cerr << "destroy not called! Renderer was not cleaned up!!\n";
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer not destroyed!");
    }
}

bool CA::Display::init(const std::string &title)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (SDL_CreateWindowAndRenderer(getPixelsX(), getPixelsY(), 0, &m_window, &m_render) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize the window/renderer: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    if (!m_text.init())
        return false;

    if (!m_text.openNewFont("Regular", CA::regularFont, 22))
        std::cerr << "Could not load new font\n";

    /*
    Test for SDL2_ttf
    texture = m_text.createTextTexture(m_render, "What does this do", "Regular", m_colors.getColor("Blue"));
    assert(texture);
    */

    SDL_SetWindowTitle(m_window, title.c_str());

    return true;
}

void CA::Display::displayGridOnScreen(const SDL_Color &c)
{
    SDL_SetRenderDrawColor(m_render, c.r, c.g, c.b, SDL_ALPHA_OPAQUE);

    for (int ix = m_displaySpacing; ix < getPixelsX(); ix += m_displaySpacing)
    {
        SDL_RenderDrawLine(m_render, ix, 0, ix, getPixelsY());
    }
    for (int iy = m_displaySpacing; iy < getPixelsY(); iy += m_displaySpacing)
    {
        SDL_RenderDrawLine(m_render, 0, iy, getPixelsX(), iy);
    }
}

void CA::Display::drawScreen(std::vector<CA::Node> &screen)
{
    SDL_Rect r;
    static bool grid = m_displayGrid;

    if (grid != m_displayGrid)
    {
        if (m_displayGrid)
        {
            displayGridOnScreen(m_colors.getColor("My Blue"));
        }
        else
        {
            displayGridOnScreen(m_colors.getColor("Default Background"));
        }
        grid = m_displayGrid;
    }

    // auto [eraseR, eraseG, eraseB] = m_colors.getColor("Black");
    // auto [paintR, paintG, paintB] = m_colors.getColor("My Red");
    SDL_Color erase = m_colors.getColor("Black");
    SDL_Color paint = m_colors.getColor("My Red");
    for (int ix = 0; ix < unitsX(); ++ix)
    {
        for (int iy = 0; iy < unitsY(); ++iy)
        {
            if (screen.at(xyToIndex(ix, iy)).dirty)
            {
                r = {(int)(ix * m_displaySpacing + 2), (int)(iy * m_displaySpacing + 2),
                     (int)(m_displaySpacing - 3), (int)(m_displaySpacing - 3)};

                if (screen.at(xyToIndex(ix, iy)).val != 0)
                {
                    SDL_SetRenderDrawColor(m_render, paint.r, paint.g, paint.b,
                                           SDL_ALPHA_OPAQUE);
                    screen.at(xyToIndex(ix, iy)).dirty = false;
                    //                  SDL_RenderFillRect(m_render, &r);
                    if (SDL_RenderDrawRect(m_render, &r) != 0)
                    {
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not write rectangle to %d,%d", ix, iy);
                    }
                }
                else
                {
                    SDL_SetRenderDrawColor(m_render, erase.r, erase.g, erase.b,
                                           SDL_ALPHA_OPAQUE);
                    screen.at(xyToIndex(ix, iy)).dirty = false;
                    //                  SDL_RenderFillRect(m_render, &r);
                    if (SDL_RenderDrawRect(m_render, &r) != 0)
                    {
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not write rectangle to %d,%d", ix, iy);
                    }
                }
            }
        }
    }

    /*
    Test to make sure SDL2_ttf is working.
    int x, y;
    SDL_QueryTexture(texture, NULL, NULL, &x, &y);
    SDL_Rect textRect = {0, 0, x, y};
    SDL_RenderCopy(m_render, texture, NULL, &textRect);
    assert(texture);
    */

    SDL_RenderPresent(m_render);
}

void CA::Display::toggleGrid()
{
    m_displayGrid = !m_displayGrid;
}

void CA::Display::destroy()
{
    if (m_render)
        SDL_DestroyRenderer(m_render);
    if (m_window)
        SDL_DestroyWindow(m_window);
    SDL_Quit();
    SDL_DestroyTexture(texture);

    m_text.destroy();

    m_render = nullptr;
    m_window = nullptr;
}