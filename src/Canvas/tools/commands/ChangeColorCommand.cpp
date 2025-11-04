#include "include/tools/commands/ChangeColorCommand.hpp"

void ChangeColorCommand::Execute()
{
  switch (m_shapeType)
  {
  case SHAPE_COLOR_CHANGE::THICKNESS:
    m_shape->GetShape()->setOutlineColor(m_newColor);
    break;
  case SHAPE_COLOR_CHANGE::FILL:
    m_shape->GetShape()->setFillColor(m_newColor);
    break;
  }
}