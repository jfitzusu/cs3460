#include "PatternBlinker.hpp"
std::array<std::array<bool, 3>, 1> PatternBlinker::m_shape = std::array<std::array<bool, 3>, 1>{ { { true, true, true } } };
std::uint8_t PatternBlinker::m_xSize = 1;
std::uint8_t PatternBlinker::m_ySize = 3;

std::uint8_t PatternBlinker::getSizeX() const
{
    return m_xSize;
}
std::uint8_t PatternBlinker::getSizeY() const
{
    return m_ySize;
}

bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= m_xSize || y >= m_ySize)
    {
        return false;
    }
    return m_shape[x][y];
}
