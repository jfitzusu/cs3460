#pragma once
#include "Renderer.hpp"

#include <memory>

class RenderConsole : public Renderer
{
  public:
    RenderConsole();

    void render(const LifeSimulator& simulation) override;

  private:
    std::unique_ptr<bool*[]> m_currentState;
    bool m_firstRender;
};