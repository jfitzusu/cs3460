#include "PatternBlock.hpp"
std::array<std::array<bool, 2>, 2> PatternBlock::m_shape = std::array<std::array<bool, 2>, 2>{ { { true, true }, { true, true } } };
std::uint8_t PatternBlock::m_xSize = 2;
std::uint8_t PatternBlock::m_ySize = 2;

std::uint8_t PatternBlock::getSizeX() const
{
    return m_xSize;
}
std::uint8_t PatternBlock::getSizeY() const
{
    return m_ySize;
}

bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= m_xSize || y >= m_ySize)
    {
        return false;
    }
    return m_shape[x][y];
}
