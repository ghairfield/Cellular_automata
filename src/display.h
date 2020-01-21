//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_DISPLAY_H
#define CELLULAR_AUTOMATA_DISPLAY_H

#include "SDL2/SDL.h"
#include "event.h"

class Display : public Event {
public:

    Display();

    bool OnInit(int x = 1200, int y = 800);

    bool Run();

    void OnEvent(SDL_Event& e) override;
    void OnExit() override;

    void DrawGrid(int spacing = 10); // Set line spacing every 10th pixel

    void OnDestroy();

    void getSize(int &x, int &y) { x = m_maxX; y = m_maxY; }
    void setGridAndDisplay(bool* grid) { m_cells = grid; }

private:

    bool m_running;
    int m_maxX, m_maxY;

    SDL_Window *m_window;
    SDL_Renderer *m_render;

    bool *m_cells;
};


#endif //CELLULAR_AUTOMATA_DISPLAY_H
