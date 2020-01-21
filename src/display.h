//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_DISPLAY_H
#define CELLULAR_AUTOMATA_DISPLAY_H

#include "SDL2/SDL.h"
#include <utility>
#include "event.h"

#define DISPLAY_MAX_X 1200
#define DISPLAY_MAX_Y 800

class Display : public Event {
public:
    static constexpr std::pair<int, int> maxSize{ DISPLAY_MAX_X, DISPLAY_MAX_Y };
    static constexpr int spacing = 10;

    Display();
    ~Display() override;

    bool OnInit();

    bool Run();

    void OnEvent(SDL_Event& e) override;
    void OnLeftMouseDown(int x, int y) override;
    void OnMouseMoveWithLeftButton(int x, int y, int rx, int ry) override;
    void OnLeftMouseUp(int x, int y) override;

    void OnExit() override;

    void DisplayGridOnScreen();

    void OnDestroy();

private:

    void getCellPosition(std::pair<int, int> &pos, int x, int y);
    void DrawScreen();

    bool m_running;

    SDL_Window *m_window;
    SDL_Renderer *m_render;

    char *m_cell;
};


#endif //CELLULAR_AUTOMATA_DISPLAY_H
