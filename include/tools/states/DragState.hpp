#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/tools/commands/DragCommand.hpp"

class DragState : public IToolState
{
public:
  DragState(const sf::Vector2f &startPos) : m_startPos(startPos) {};
  void HandleEvent(CCanvas *canvas) override;

private:
  sf::Vector2f m_startPos;
};
