#ifndef CELLULAR_AUTOMATA_UNIT_H
#define CELLULAR_AUTOMATA_UNIT_H

#include <cstdint>
#include <assert.h>

namespace CA
{

  /**
   * @brief Describes a unit and its actions on the screen which is
   * made up of a group of pixels.
   *
   */
  class Unit
  {
  public:
    /**
     * @brief Construct a new Unit object.
     *
     * @param maxX Size in pixels of screen width
     * @param maxY Size in pixels of screen height
     * @param spacing Square number of pixels that make up a unit. Each `unit`
     * is spacing * spacing square.
     */
    Unit(uint32_t maxX, uint32_t maxY, uint32_t spacing)
        : m_displayMaxX(maxX), m_displayMaxY(maxY), m_displaySpacing(spacing)
    {
      // The spacing needs to divide the board evenly.
      assert((maxX % 2 == 0) && (maxY % 2 == 0) && (spacing % 2 == 0));
    }

    // Do not initialize an incomplete object
    Unit() = delete;

    ~Unit() = default;

    /**
     * @brief Copy constructor
     *
     * @param other Unit to copy
     */
    Unit(const Unit &other)
    {
      m_displayMaxX = other.m_displayMaxX;
      m_displayMaxY = other.m_displayMaxY;
      m_displaySpacing = other.m_displaySpacing;
    }

    /**
     * @brief Helper to reterive the size of the `unit` board.
     *
     * @return uint32_t Size of the `unit` board. Should equal the size
     * of the board (not screen).
     */
    inline uint32_t maxVec()
    {
      return (uint32_t)((m_displayMaxX / m_displaySpacing) *
                        (m_displayMaxY / m_displaySpacing));
    }

    /**
     * @brief Returns the vector index which x,y belongs to. The vector
     * is stored in row major order.
     *
     * @param x X position in pixels on screen
     * @param y Y position in pixels on screen
     * @return uint32_t position in display vector
     */
    inline uint32_t xyToIndex(uint32_t x, uint32_t y) const noexcept
    {
      return x + (y * (m_displayMaxX / m_displaySpacing));
    }

    /**
     * @brief Get the number of units making up the width.
     *
     * @return uint32_t Number of X units
     */
    inline uint32_t unitsX() const noexcept
    {
      return m_displayMaxX / m_displaySpacing;
    }

    /**
     * @brief Get the number of units making up the height
     *
     * @return uint32_t Number of Y units
     */
    inline uint32_t unitsY() const noexcept
    {
      return m_displayMaxY / m_displaySpacing;
    }

    /**
     * @brief Helper to get the number of pixels. Ensures that it is known
     * we are not retriving units, but pixels.
     *
     * @return uint32_t Pixels of X size
     */
    inline uint32_t getPixelsX()
    {
      return m_displayMaxX;
    }

    /**
     * @brief Helper to get the number of pixels. Ensures that it is known
     * we are not retriving units, but pixels.
     *
     * @return uint32_t Pixels of Y size
     */
    inline uint32_t getPixelsY()
    {
      return m_displayMaxY;
    }

    /**
     * @brief Helper to change mouse pixel clicks to `unit` measurement.
     * The rest of this class operates on x,y in the `unit` domain.
     *
     * @param x Click position x
     * @param y Click position y
     * @return std::pair<uint32_t, uint32_t> `unit` coordinate pair.
     */
    inline std::pair<uint32_t, uint32_t>
    pixelToUnitPosition(uint32_t x, uint32_t y)
    {
      std::pair<uint32_t, uint32_t> unit;
      unit.first = x / m_displaySpacing;
      unit.second = y / m_displaySpacing;

      return unit;
    }

  protected:
    uint32_t m_displaySpacing; // Square pixels, or `units`
  private:
    uint32_t m_displayMaxX, m_displayMaxY; // In pixels
  };

} /* namespace CA */

#endif /* CELLULAR_AUTOMATA_UNIT_H */