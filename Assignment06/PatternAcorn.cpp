#include "PatternAcorn.hpp"
std::array<std::array<bool, 3>, 7> PatternAcorn::m_shape = std::array<std::array<bool, 3>, 7>{ { { true, false, false },
                                                                                                 { true, false, true },
                                                                                                 { false, false, false },
                                                                                                 { false, true, false },
                                                                                                 { true, false, false },
                                                                                                 { true, false, false },
                                                                                                 { true, false, false } } };
std::uint8_t PatternAcorn::m_xSize = 7;
std::uint8_t PatternAcorn::m_ySize = 3;

std::uint8_t PatternAcorn::getSizeX() const
{
    return m_xSize;
}
std::uint8_t PatternAcorn::getSizeY() const
{
    return m_ySize;
}

bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= m_xSize || y >= m_ySize)
    {
        return false;
    }
    return m_shape[x][y];
}
