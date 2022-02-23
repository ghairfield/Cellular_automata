//
// Created by g on 1/20/20.
//

#include "event.h"

void CA::Event::onEvent(SDL_Event &e)
{
    static bool leftMouseDown = false;
    static bool rightMouseDown = false;

    switch (e.type)
    {
    case SDL_KEYDOWN:
        onKeyDown(e.key.keysym.scancode, e.key.keysym.mod);
        break;
    case SDL_KEYUP:
        onKeyUp(e.key.keysym.scancode, e.key.keysym.mod);
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            leftMouseDown = true;
            onLeftMouseDown(e.button.x, e.button.y);
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            rightMouseDown = true;
            onRightMouseDown(e.button.x, e.button.y);
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            leftMouseDown = false;
            onLeftMouseUp(e.button.x, e.button.y);
        }
        else if (e.button.button == SDL_BUTTON_RIGHT)
        {
            rightMouseDown = false;
            onRightMouseUp(e.button.x, e.button.y);
        }
        break;
    case SDL_MOUSEMOTION:
        if (leftMouseDown && !rightMouseDown)
            onMouseMoveWithLeftButton(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
        else if (rightMouseDown && !leftMouseDown)
            onMouseMoveWithRightButton(e.motion.x, e.motion.y, e.motion.xrel, e.motion.yrel);
        else
            onMouseMotion();
        break;
    case SDL_QUIT:
        onExit();
        break;
    }
}
