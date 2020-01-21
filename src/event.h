//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_EVENT_H
#define CELLULAR_AUTOMATA_EVENT_H

#include <SDL2/SDL_events.h>

class Event {
public:
    Event() = default;;
    virtual ~Event() = default;;

    virtual void OnEvent(SDL_Event& e);

    virtual void OnKeyDown(SDL_Scancode key, Uint16 mod) {};
    virtual void OnKeyUp(SDL_Scancode key, Uint16 mod) {};
    virtual void OnExit() {};
};


#endif //CELLULAR_AUTOMATA_EVENT_H
