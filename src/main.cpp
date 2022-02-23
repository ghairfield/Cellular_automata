#include <iostream>
#include "game.h"

#define DISPLAY_MAX_X 1200
#define DISPLAY_MAX_Y 800
#define DISPLAY_SPACING 8 // Smallest that has been tested with.

int main()
{
    CA::Game g(DISPLAY_MAX_X, DISPLAY_MAX_Y, DISPLAY_SPACING);
    if (!g.init())
        return EXIT_FAILURE;
    g.run();
    g.destroy();

    return 0;
}