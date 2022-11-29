#include "RendererConsole.hpp"

#include "rlutil.h"

#include <thread>

RenderConsole::RenderConsole()
{
    m_firstRender = true;
}

void RenderConsole::render(const LifeSimulator& simulation)
{
    rlutil::hidecursor();
    if (m_firstRender)
    {
        rlutil::cls();
        m_firstRender = false;
        m_currentState = std::make_unique<bool*[]>(simulation.getSizeX());
        for (int i = 0; i < simulation.getSizeX(); i++)
        {
            m_currentState[i] = new bool[simulation.getSizeY()];
            for (int j = 0; j < simulation.getSizeY(); j++)
            {
                m_currentState[i][j] = false;
            }
        }
    }

    for (std::uint8_t i = 0; i < simulation.getSizeX(); i++)
    {
        for (std::uint8_t j = 0; j < simulation.getSizeY(); j++)
        {
            if (simulation.getCell(i, j) != m_currentState[i][j])
            {
                m_currentState[i][j] = simulation.getCell(i, j);
                rlutil::locate(i + 1, j + 1);
                rlutil::setChar('X');
                if (simulation.getCell(i, j))
                {
                    rlutil::setChar('X');
                }
                else
                {
                    rlutil::setChar(' ');
                }
            }
        }
    }

    std::cout << std::flush;
    rlutil::locate(1, 1);
    rlutil::showcursor();
}