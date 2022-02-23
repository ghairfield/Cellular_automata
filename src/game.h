#ifndef CELLULAR_AUTOMATA_GAME_H
#define CELLULAR_AUTOMATA_GAME_H

#include <memory>
#include <chrono>
#include "event.h"
#include "display.h"
#include "cgl.h"

namespace CA
{

  class Game : public Event, public Unit
  {
  public:
    /**
     * @brief Construct a new Game object with default values. See @init
     * for initialization.
     *
     * @param maxX Maximum number of horizontal pixels.
     * @param maxY Maximum number of vertical pixels.
     * @param spacing Square cell size.
     *
     */
    Game(uint32_t maxX, uint32_t maxY, uint32_t spacing);

    ~Game();

    /**
     * @brief Calls the init functions for Display and CGL
     *
     * @return true Initialization was successful.
     * @return false Initialization failed.
     */
    bool init();

    /**
     * @brief Starts the program in *draw* mode.
     *
     */
    void run();

    /**
     * @brief Calls for Display and CGL to terminate.
     *
     */
    void destroy();

  private:
    /**
     * @brief Set the Cell Position at index to value
     *
     * @param x `Unit` X position
     * @param y `Unit` Y position
     * @param value Value to set it to
     */
    void setCellPosition(uint32_t x, uint32_t y, uint32_t value);

    /**
     * @brief Starts passing @m_board to `CGL` to run game. All input
     * is paused until `R` is presses again to stop `CGL`.
     *
     */
    void startConways();

    /**
     * @brief Clears the game board
     *
     */
    void clearBoard();

    void decreaseDelay();

    void increaseDelay();

    /// SDL event handlers
    void onEvent(SDL_Event &e) override;
    void onKeyDown(SDL_Scancode key, Uint16 mod) override;
    void onLeftMouseDown(int x, int y) override;
    void onMouseMoveWithLeftButton(int x, int y, int rx, int ry) override;
    void onRightMouseDown(int x, int y) override;
    void onMouseMoveWithRightButton(int x, int y, int rx, int ry) override;
    void onExit() override;

    std::unique_ptr<CA::Display> m_pDisp; // Handle to display
    std::unique_ptr<CA::CGL> m_pCGL;      // Handle to CGL
    std::vector<CA::Node> m_board;        // Board we are operating on
    bool m_running, m_cglStart;
    std::chrono::milliseconds m_delay;       // Delay in ms between `CGL` updates
    std::chrono::milliseconds m_delayChange; // Change to @m_delay when arrow
                                             // buttons are used
  };

} /* namespace CA */

#endif /* CELLULAR_AUTOMATA_GAME_H */