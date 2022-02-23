//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_EVENT_H
#define CELLULAR_AUTOMATA_EVENT_H

#include <SDL2/SDL_events.h>

namespace CA
{

    class Event
    {
    public:
        Event() = default;
        virtual ~Event() = default;

        virtual void onEvent(SDL_Event &e);

        // Events, must override
        virtual void onKeyDown(SDL_Scancode key, Uint16 mod){};
        virtual void onKeyUp(SDL_Scancode key, Uint16 mod){};

        virtual void onLeftMouseDown(int x, int y){};
        virtual void onLeftMouseUp(int x, int y){};
        virtual void onRightMouseDown(int x, int y){};
        virtual void onRightMouseUp(int x, int y){};
        virtual void onMouseMoveWithLeftButton(int x, int y, int rx, int ry){};
        virtual void onMouseMoveWithRightButton(int x, int y, int rx, int ry){};
        virtual void onMouseMotion(){};

        virtual void onExit(){};
    };

} /* namespace CA */

#endif // CELLULAR_AUTOMATA_EVENT_H
