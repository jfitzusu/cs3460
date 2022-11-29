#include "LifeSimulator.hpp"

#include "Pattern.hpp"

#include <algorithm>
#include <iostream>
#include <memory>

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY)
{
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    m_state = std::make_unique<bool*[]>(sizeX);
    for (std::uint8_t i = 0; i < sizeX; i++)
    {
        m_state[i] = new bool[sizeY];
        for (std::uint8_t j = 0; j < sizeY; j++)
        {
            m_state[i][j] = false;
        }
    }
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{
    for (std::uint8_t i = startX; i < std::min(pattern.getSizeX() + startX, static_cast<int>(m_sizeX)); i++)
    {
        for (std::uint8_t j = startY; j < std::min(pattern.getSizeY() + startY, static_cast<int>(m_sizeY)); j++)
        {
            m_state[i][j] = pattern.getCell(i - startX, j - startY);
        }
    }
}

void LifeSimulator::update()
{
    std::unique_ptr<bool*[]> newState = std::make_unique<bool*[]>(m_sizeX);

    for (std::uint8_t i = 0; i < m_sizeX; i++)
    {
        newState[i] = new bool[m_sizeY];
        for (std::uint8_t j = 0; j < m_sizeY; j++)
        {
            std::uint8_t count = countNeighbors(i, j);
            if (count == 3)
            {
                newState[i][j] = true;
            }
            else if (count == 2)
            {
                newState[i][j] = m_state[i][j];
            }
            else
            {
                newState[i][j] = false;
            }
        }
    }

    for (std::uint8_t i = 0; i < m_sizeX; i++)
    {
        for (std::uint8_t j = 0; j < m_sizeY; j++)
        {
            m_state[i][j] = newState[i][j];
        }
    }
}

std::uint8_t LifeSimulator::countNeighbors(std::uint8_t x, std::uint8_t y)
{
    if ((x >= m_sizeX || y >= m_sizeY))
    {
        return 0;
    }

    std::uint8_t count = 0;
    for (std::uint8_t i = static_cast<std::uint8_t>(std::max(x - 1, 0)); i <= static_cast<std::uint8_t>(std::min(x + 1, static_cast<int>(m_sizeX) - 1)); i++)
    {
        for (std::uint8_t j = static_cast<std::uint8_t>(std::max(y - 1, 0)); j <= static_cast<std::uint8_t>(std::min(y + 1, static_cast<int>(m_sizeY) - 1)); j++)
        {
            if (m_state[i][j] && !(i == x && j == y))
            {

                count++;
            }
        }
    }

    return count;
}

std::uint8_t LifeSimulator::getSizeX() const
{
    return m_sizeX;
}
std::uint8_t LifeSimulator::getSizeY() const
{
    return m_sizeY;
}

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    return m_state[x][y];
}
