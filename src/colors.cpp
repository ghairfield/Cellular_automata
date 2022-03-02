#include "colors.h"

CA::Colors::Colors()
{
  // Create some basic colors.
  m_colors.emplace("Red", SDL_Color{255, 0, 0});
  m_colors.emplace("Green", SDL_Color{0, 255, 0});
  m_colors.emplace("Blue", SDL_Color{0, 0, 255});
  m_colors.emplace("White", SDL_Color{255, 255, 255});
  m_colors.emplace("Black", SDL_Color{0, 0, 0});
  m_colors.emplace("My Blue", SDL_Color{3, 152, 252});
  m_colors.emplace("My Red", SDL_Color{255, 11, 0});

  // Some defaults
  m_colors.emplace("Default Background", SDL_Color{0, 0, 0});
  m_colors.emplace("Default Foreground", SDL_Color{255, 255, 255});
}

bool CA::Colors::createColor(const std::string &name,
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

SDL_Color CA::Colors::getColor(const std::string &name)
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
