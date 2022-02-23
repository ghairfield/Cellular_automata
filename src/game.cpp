#include <algorithm>
#include <assert.h>
#include "game.h"

using namespace std::chrono_literals;

CA::Game::Game(uint32_t maxX, uint32_t maxY, uint32_t spacing)
    : m_running(false), m_pDisp(nullptr), m_pCGL(nullptr),
      m_cglStart(false), m_delay(500ms), m_delayChange(10ms),
      Unit(maxX, maxY, spacing),
      m_board((maxX / spacing) * (maxY / spacing),
              CA::Node())
{
  assert(spacing >= 8);               // Hard coded smallest cell size
  assert(maxX >= 100 && maxY >= 100); // Smallest that has been tested.
}

CA::Game::~Game()
{
}

bool CA::Game::init()
{
  m_pDisp = std::make_unique<Display>(getPixelsX(),
                                      getPixelsY(), m_displaySpacing);

  if (!m_pDisp->init("Conway Game of Life"))
  {
    return false;
  }

  m_pCGL = std::make_unique<CGL>(getPixelsX(), getPixelsY(), m_displaySpacing);

  return true;
}

void CA::Game::run()
{
  m_running = true;

  SDL_Event event;
  auto t1 = std::chrono::steady_clock::now();

  while (m_running)
  {
    while (SDL_PollEvent(&event))
      onEvent(event);
    auto t2 = std::chrono::steady_clock::now();
    if ((t2 - t1) > std::chrono::milliseconds(10))
    {
      m_pDisp->drawScreen(m_board);
      t1 = t2;
    }

    if (m_cglStart)
    {
      startConways();
    }
  }
}

void CA::Game::startConways()
{
  SDL_Event event;
  auto t1 = std::chrono::steady_clock::now();
  std::vector<CA::Node> step;

  while (m_cglStart)
  {
    while (SDL_PollEvent(&event))
      onEvent(event);

    auto t2 = std::chrono::steady_clock::now();
    while ((t2 - t1) > m_delay)
    {
      step = m_pCGL->step(m_board);
      m_pDisp->drawScreen(step);
      m_board = std::move(step);
      t1 = t2;
    }
  }
}

void CA::Game::destroy()
{
  m_pDisp->destroy();
}

void CA::Game::increaseDelay()
{
  if (m_delay + m_delayChange > 3000ms)
    return;
  m_delay += m_delayChange;
}

void CA::Game::decreaseDelay()
{
  if (m_delay - m_delayChange < 10ms)
    return;
  m_delay -= m_delayChange;
}

void CA::Game::onEvent(SDL_Event &e)
{
  Event::onEvent(e);
}

void CA::Game::onExit()
{
  m_running = false;
}

void CA::Game::setCellPosition(uint32_t x, uint32_t y, uint32_t value)
{
  if (m_cglStart)
    return; // No drawing while CGL is going

  std::pair<uint32_t, uint32_t> t = pixelToUnitPosition(x, y);
  uint32_t index = xyToIndex(t.first, t.second);
  m_board.at(index).val = value;
  m_board.at(index).dirty = true;
}

void CA::Game::clearBoard()
{
  for (auto &each : m_board)
  {
    if (each.val)
    {
      each.val = 0;
      each.dirty = true;
    }
  }
}

void CA::Game::onLeftMouseDown(int x, int y)
{
  setCellPosition(x, y, 1);
}

void CA::Game::onMouseMoveWithLeftButton(int x, int y, int rx, int ry)
{
  setCellPosition(x, y, 1);
}

void CA::Game::onRightMouseDown(int x, int y)
{
  setCellPosition(x, y, 0);
}

void CA::Game::onMouseMoveWithRightButton(int x, int y, int rx, int ry)
{
  setCellPosition(x, y, 0);
}

void CA::Game::onKeyDown(SDL_Scancode key, Uint16 mod)
{
  switch (key)
  {
  case SDL_SCANCODE_C:
    if (!m_cglStart)
    {
      clearBoard();
    }
    break;
  case SDL_SCANCODE_G:
    m_pDisp->toggleGrid();
    break;
  case SDL_SCANCODE_R:
    m_cglStart = !m_cglStart;
    break;
  case SDL_SCANCODE_LEFT:
    if (m_cglStart)
    {
      increaseDelay();
    }
    break;
  case SDL_SCANCODE_RIGHT:
    if (m_cglStart)
    {
      decreaseDelay();
    }
    break;
  }
}
