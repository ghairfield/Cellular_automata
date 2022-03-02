#include <cassert>
#include "textDisplay.h"

bool CA::TextDisplay::init()
{
  return TTF_Init() == 0;
}

void CA::TextDisplay::destroy()
{
  for (auto font : fonts)
  {
    if (font.second)
      TTF_CloseFont(font.second);
  }
  TTF_Quit();
}

SDL_Texture *
CA::TextDisplay::createTextTexture(SDL_Renderer *rend, const std::string &text,
                                   const std::string &font, const SDL_Color &color)
{
  std::map<std::string, TTF_Font *>::const_iterator it;
  it = fonts.find(font);
  if (it == fonts.end())
    return nullptr;

  SDL_Surface *surface = TTF_RenderText_Solid(it->second, text.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surface);
  SDL_FreeSurface(surface);

  assert(texture);
  return texture;
}

bool CA::TextDisplay::openNewFont(const std::string &name,
                                  const std::string &fontLocation, uint32_t size)
{
  std::map<std::string, TTF_Font *>::const_iterator it;
  it = fonts.find(name);
  if (it != fonts.end())
  {
    return true;
  }

  TTF_Font *f = TTF_OpenFont(fontLocation.c_str(), size);
  if (!f)
  {
    return false;
  }

  fonts.emplace(name, f);
  return true;
}