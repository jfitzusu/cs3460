#pragma once
#include "Pattern.hpp"

#include <array>

class PatternGlider : public Pattern
{
  public:
    std::uint8_t getSizeX() const override;
    std::uint8_t getSizeY() const override;
    bool getCell(std::uint8_t x, std::uint8_t y) const override;

  private:
    static std::array<std::array<bool, 3>, 3> m_shape;
    static std::uint8_t m_xSize;
    static std::uint8_t m_ySize;
};