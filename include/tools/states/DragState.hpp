#pragma once

#include "include/tools/states/IToolState.hpp"
#include "include/tools/commands/DragCommand.hpp"
#include "include/tools/commands/GroupShapesCommand.hpp"
#include "include/tools/commands/UngroupShapesCommand.hpp"

class DragState : public IToolState
{
public:
  DragState(const sf::Vector2f &startPos) : m_startPos(startPos) {};
  void HandleEvent(CCanvas *canvas) override;

private:
  sf::Vector2f m_startPos;
  std::unique_ptr<DragCommand> m_activeCommand;
};
