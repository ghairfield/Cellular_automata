//
// Created by g on 1/20/20.
//

#include "event.h"

void Event::OnEvent(SDL_Event& e) {
    static bool leftMouseDown = false;
    static bool rightMouseDown = false;

    switch (e.type) {
        case SDL_KEYDOWN:
            OnKeyDown(e.key.keysym.scancode, e.key.keysym.mod);
            break;
        case SDL_KEYUP:
            OnKeyUp(e.key.keysym.scancode, e.key.keysym.mod);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) { leftMouseDown = true; OnLeftMouseDown(e.button.x, e.button.y); }
            else if (e.button.button == SDL_BUTTON_RIGHT) { rightMouseDown =  true; OnRightMouseDown(e.button.x, e.button.y); }
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT) { leftMouseDown = false; OnLeftMouseUp(e.button.x, e.button.y); }
            else if (e.button.button == SDL_BUTTON_RIGHT) { rightMouseDown = false; OnRightMouseUp(e.button.x, e.button.y); }
            break;
        case SDL_MOUSEMOTION:
            if (leftMouseDown && !rightMouseDown) OnMouseMoveWithLeftButton(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            else if (rightMouseDown && !leftMouseDown) OnMouseMoveWithRightButton(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
            else OnMouseMotion();
            break;
        case SDL_QUIT:
            OnExit();
            break;
    }
}
