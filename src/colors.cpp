#include "colors.h"

std::map<std::string, SDL_Color> CA::Colors::m_colors = {
    {"Red", SDL_Color{255, 0, 0}},
    {"Green", SDL_Color{0, 255, 0}},
    {"Blue", SDL_Color{0, 0, 255}},
    {"White", SDL_Color{255, 255, 255}},
    {"Orange", SDL_Color{209, 103, 27}},
    {"Pink", SDL_Color{255, 0, 140}},
    {"Light Blue", SDL_Color{72, 162, 207}},
    {"Black", SDL_Color{0, 0, 0}},
    {"My Blue", SDL_Color{3, 152, 252}},
    {"My Red", SDL_Color{255, 11, 0}},
    {"Default Background", SDL_Color{0, 0, 0}},
    {"Default Foreground", SDL_Color{255, 255, 255}},
};
