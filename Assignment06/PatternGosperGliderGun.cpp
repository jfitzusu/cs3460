#include "PatternGosperGliderGun.hpp"
std::array<std::array<bool, 9>, 36> PatternGosperGliderGun::m_shape = std::array<std::array<bool, 9>, 36>{ { { false, false, false, true, true, false, false, false, false },
                                                                                                             { false, false, false, true, true, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, true, true, true, false, false, false, false },
                                                                                                             { false, true, false, false, false, true, false, false, false },
                                                                                                             { true, false, false, false, false, false, true, false, false },
                                                                                                             { true, false, false, false, false, false, true, false, false },
                                                                                                             { false, false, false, true, false, false, false, false, false },
                                                                                                             { false, true, false, false, false, true, false, false, false },
                                                                                                             { false, false, true, true, true, false, false, false, false },
                                                                                                             { false, false, false, true, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, true, true, true, false, false },
                                                                                                             { false, false, false, false, true, true, true, false, false },
                                                                                                             { false, false, false, true, false, false, false, true, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, true, true, false, false, false, true, true },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, false, false, false, false },
                                                                                                             { false, false, false, false, false, true, true, false, false },
                                                                                                             { false, false, false, false, false, true, true, false, false } } };
std::uint8_t PatternGosperGliderGun::m_xSize = 36;
std::uint8_t PatternGosperGliderGun::m_ySize = 9;

std::uint8_t PatternGosperGliderGun::getSizeX() const
{

    return m_xSize;
}
std::uint8_t PatternGosperGliderGun::getSizeY() const
{
    return m_ySize;
}

bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    if (x >= m_xSize || y >= m_ySize)
    {
        return false;
    }
    return m_shape[x][y];
}
