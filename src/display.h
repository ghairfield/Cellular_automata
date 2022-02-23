//
// Created by g on 1/20/20.
//

#ifndef CELLULAR_AUTOMATA_DISPLAY_H
#define CELLULAR_AUTOMATA_DISPLAY_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "event.h"
#include "node.h"
#include "unit.h"

namespace CA
{
    class Display : public Unit
    {
    public:
        Display() = delete;

        /**
         * @brief Construct a new Display object. Use @init for actual
         * SDL initialization
         *
         * @param maxX Max width in pixels
         * @param maxY Max height in pixels
         * @param space A `unit` of pixels that represents a cell
         * @see init()
         */
        Display(uint32_t maxX, uint32_t maxY, uint32_t space);
        ~Display();

        /**
         * @brief Initialize the SDL environment and set the screen size.
         *
         * @param title Title of the screen
         * @return true SDL was initialized successfully
         * @return false There was a problem
         *
         * @todo Change to throw an error
         */
        bool init(const std::string &title);

        /**
         * @brief Prints the contents of screen to display. Drawing is affected
         * by m_displaySpacing, each CA::Node in the screen is assumed to be
         * a SDL_Rect.
         *
         */
        void drawScreen(std::vector<CA::Node> &screen);

        /**
         * @brief Draw a grid on screen. This is spaced by DISPLAY_SPACING
         * and drawn horizontally and vertically.
         *
         * @param d Display it read or black
         *
         * @todo The param should go and should be replaced by something
         * better.
         */
        void displayGridOnScreen(bool d);

        /**
         * @brief Toggles if the grid is displayed on the screen.
         *
         */
        void toggleGrid();

        /**
         * @brief Destroys all allocated assets.
         *
         */
        void destroy();

    private:
        bool m_displayGrid;

        SDL_Window *m_window;
        SDL_Renderer *m_render;
    };

} /* namespace CA */

#endif // CELLULAR_AUTOMATA_DISPLAY_H
