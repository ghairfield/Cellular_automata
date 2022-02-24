#include "colors.h"

CA::Colors::Colors()
{
  // Create some basic colors.
  m_colors.emplace("Red", Color(255, 0, 0));
  m_colors.emplace("Green", Color(0, 255, 0));
  m_colors.emplace("Blue", Color(0, 0, 255));
  m_colors.emplace("White", Color(255, 255, 255));
  m_colors.emplace("Black", Color(0, 0, 0));
  m_colors.emplace("My Blue", Color(3, 152, 252));
  m_colors.emplace("My Red", Color(255, 11, 0));

  // Some defaults
  m_colors.emplace("Default Background", Color(0, 0, 0));
  m_colors.emplace("Default Foreground", Color(255, 255, 255));
}

bool CA::Colors::createColor(const std::string &name,
                             uint8_t r, uint8_t g, uint8_t b)
{
  auto itr = m_colors.find(name);
  if (itr == m_colors.end())
  {
    return false;
  }

  m_colors.emplace(name, Color(r, g, b));
  return true;
}

CA::Color CA::Colors::getColor(const std::string &name)
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
