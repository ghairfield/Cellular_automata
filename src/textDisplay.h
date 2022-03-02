#ifndef CELLULAR_AUTOMATA_TEXT_DISPLAY_H
#define CELLULAR_AUTOMATA_TEXT_DISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <map>
#include "colors.h"

namespace CA
{
  // TODO the paths need to change. Fix for cmake directory
  static const char regularFont[] = "../assets/JosefinSans-Regular.ttf";
  static const char boldFont[] = "../assets/JosefinSans-Bold.ttf";
  static const char italicFont[] = "../assets/JosefinSans-Italic.ttf";

  class TextDisplay
  {
  public:
    /**
     * @brief Initialize TTF_font library
     *
     * @return true If library was initialized
     * @return false If there was a problem.
     */
    bool init();

    /**
     * @brief Clean up all fonts and call TTF_Quit
     *
     */
    void destroy();

    SDL_Texture *createTextTexture(SDL_Renderer *rend, const std::string &text,
                                   const std::string &font, const Color &color);

    bool openNewFont(const std::string &name,
                     const std::string &fontLocation, uint32_t size);

  private:
    // TODO create map of fonts so no reloading of them
    std::map<std::string, TTF_Font *> fonts;
    SDL_Color color;
  };

} /* namespace CA */

#endif /* CELLULAR_AUTOMATA_TEXT_DISPLAY_H */