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
#define DISPLAY_SPACING 10
#define DISPLAY_MAX_ARR ((DISPLAY_MAX_X / DISPLAY_SPACING) * (DISPLAY_MAX_Y / DISPLAY_SPACING))
#define ARR_XY(x,y) ((x) + ((y) * (DISPLAY_MAX_X / DISPLAY_SPACING)))
#define MAX_ARR_X (DISPLAY_MAX_X / DISPLAY_SPACING)
#define MAX_ARR_Y (DISPLAY_MAX_Y / DISPLAY_SPACING)

class Node {
public:
    char val;
    bool dirty;
};

class Display : public Event {
public:
    static constexpr std::pair<int, int> maxSize{ DISPLAY_MAX_X, DISPLAY_MAX_Y };

    Display();
    ~Display() override;

    bool OnInit();

    bool Run();

    void OnEvent(SDL_Event& e) override;

    void OnKeyDown(SDL_Scancode key, Uint16 mod) override;

    void OnLeftMouseDown(int x, int y) override;
    void OnMouseMoveWithLeftButton(int x, int y, int rx, int ry) override;
    void OnRightMouseDown(int x, int y) override;
    void OnMouseMoveWithRightButton(int x, int y, int rx, int ry) override;

    void OnExit() override;

    void DisplayGridOnScreen(bool d);

    void OnDestroy();

private:

    static void getCellPosition(std::pair<int, int> &pos, int x, int y);
    void writeCellPosition(std::pair<int, int> & pos, char val);

    bool m_running;
    bool m_displayGrid;

    SDL_Window *m_window;
    SDL_Renderer *m_render;

    Node *m_cell;
    void DrawScreen();
    void clearCells();
};


#endif //CELLULAR_AUTOMATA_DISPLAY_H
