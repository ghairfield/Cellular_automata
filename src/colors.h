
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
    Colors() = delete;

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
    static bool createColor(const std::string &name,
                            uint8_t r, uint8_t g, uint8_t b)
    {
      auto itr = m_colors.find(name);
      if (itr == m_colors.end())
      {
        return false;
      }

      m_colors.emplace(name, SDL_Color{r, g, b});
      return true;
    }

    /**
     * @brief Create a Color object
     *
     * @param name Name for the color, used to lookup the color
     * @param c SDL_Color
     * @return true Color was created
     * @return false Another color with @name exists
     */
    static bool createColor(const std::string &name, const SDL_Color &c)
    {
      return Colors::createColor(name, c.r, c.g, c.b);
    }

    /**
     * @brief Get a color object. If no object exits, it returns the
     * default foreground color.
     *
     * @param name Name to lookup
     * @return A Color object or default foreground
     * @todo Need a better return scheme here
     */
    static SDL_Color getColor(const std::string &name)
    {
      auto itr = m_colors.find(name);
      if (itr == m_colors.end())
      {
        // TODO figure out something better to do here.
        // -- maybe optional??
        return m_colors.at("Default Foreground");
      }
      else
        return m_colors.at(name);
    }

  private:
    static std::map<std::string, SDL_Color> m_colors;
  };

} /* namespace CA */

#endif /* CELLULAR_AUTOMATA_COLORS_H */