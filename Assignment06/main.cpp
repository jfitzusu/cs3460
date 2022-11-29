#include "LifeSimulator.hpp"
#include "Pattern.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "RendererConsole.hpp"
#include "rlutil.h"

#include <iostream>
#include <memory>
#include <thread>

int main()
{

    // Accorn
    LifeSimulator lifeSimulator = LifeSimulator(static_cast<std::uint8_t>(rlutil::tcols()), static_cast<std::uint8_t>(rlutil::trows()));
    lifeSimulator.insertPattern(PatternAcorn(), 40, 10);
    RenderConsole renderer = RenderConsole();

    for (int i = 0; i < 100; i++)
    {
        renderer.render(lifeSimulator);
        lifeSimulator.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Blinker
    LifeSimulator lifeSimulator2 = LifeSimulator(static_cast<std::uint8_t>(rlutil::tcols()), static_cast<std::uint8_t>(rlutil::trows()));
    lifeSimulator2.insertPattern(PatternBlinker(), 20, 20);

    for (int i = 0; i < 100; i++)
    {
        renderer.render(lifeSimulator2);
        lifeSimulator2.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Block
    LifeSimulator lifeSimulator3 = LifeSimulator(static_cast<std::uint8_t>(rlutil::tcols()), static_cast<std::uint8_t>(rlutil::trows()));
    lifeSimulator3.insertPattern(PatternBlock(), 20, 20);

    for (int i = 0; i < 100; i++)
    {
        renderer.render(lifeSimulator3);
        lifeSimulator3.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Glider
    LifeSimulator lifeSimulator4 = LifeSimulator(static_cast<std::uint8_t>(rlutil::tcols()), static_cast<std::uint8_t>(rlutil::trows()));
    lifeSimulator4.insertPattern(PatternGlider(), 20, 20);

    for (int i = 0; i < 100; i++)
    {
        renderer.render(lifeSimulator4);
        lifeSimulator4.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Glider Gun
    LifeSimulator lifeSimulator5 = LifeSimulator(static_cast<std::uint8_t>(rlutil::tcols()), static_cast<std::uint8_t>(rlutil::trows()));
    lifeSimulator5.insertPattern(PatternGosperGliderGun(), 20, 20);

    for (int i = 0; i < 100; i++)
    {
        renderer.render(lifeSimulator5);
        lifeSimulator5.update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    rlutil::cls();
}