//
// Created by g on 1/20/20.
//

#include "event.h"

void Event::OnEvent(SDL_Event& e) {
    switch (e.type) {
        case SDL_KEYDOWN:
            OnKeyDown(e.key.keysym.scancode, e.key.keysym.mod);
            break;
        case SDL_KEYUP:
            OnKeyUp(e.key.keysym.scancode, e.key.keysym.mod);
            break;
        case SDL_QUIT:
            OnExit();
            break;
    }
}
