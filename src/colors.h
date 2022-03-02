
#ifndef CELLULAR_AUTOMATA_COLORS_H
#define CELLULAR_AUTOMATA_COLORS_H

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <tuple>
#include <cstdint>

namespace CA
{
  class Colors
  {
  public:
    /**
     * @brief Construct a new Colors object with some basic colors.
     *
     */
    Colors();

    /**
     * @brief Create a new color
     *
     * @param name Name for color, used to lookup the color.
     * @param r Red value (0 - 255 inclusive)
     * @param g Green value (0 - 255 inclusive)
     * @param b Blue value (0 - 255 inclusive)
     * @return true Color was created
     * @return false Another color with @name exists
     */
    bool createColor(const std::string &name, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Get a color object. If no object exits, it returns the
     * default foreground color.
     *
     * @param name Name to lookup
     * @return A Color object or default foreground
     * @todo Need a better return scheme here
     */
    SDL_Color getColor(const std::string &name);

  private:
    std::map<std::string, SDL_Color> m_colors;
  };

} /* namespace CA */

#endif /* CELLULAR_AUTOMATA_COLORS_H */