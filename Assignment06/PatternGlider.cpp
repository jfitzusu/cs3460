#include "PatternGlider.hpp"
std::array<std::array<bool, 3>, 3> PatternGlider::m_shape = std::array<std::array<bool, 3>, 3>{ { { true, false, false }, { true, false, true }, { true, true, false } } };
std::uint8_t PatternGlider::m_xSize = 3;
std::uint8_t PatternGlider::m_ySize = 3;

std::uint8_t PatternGlider::getSizeX() const
{
    return m_xSize;
}
std::uint8_t PatternGlider::getSizeY() const
{
    return m_ySize;
}

bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= m_xSize || y >= m_ySize)
    {
        return false;
    }
    return m_shape[x][y];
}
