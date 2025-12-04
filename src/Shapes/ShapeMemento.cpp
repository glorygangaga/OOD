#include "include/shapes/ShapeMemento.hpp"

sf::Color ShapeMemento::GetFillColor() const
{
  return m_fillColor;
}

sf::Color ShapeMemento::GetOutlineColor() const
{
  return m_outlineColor;
}

unsigned int ShapeMemento::GetThickness() const
{
  return m_thickness;
}

sf::Vector2f ShapeMemento::GetPosition() const
{
  return m_position;
}

void ShapeMemento::SetFillColor(const sf::Color &newColor)
{
  m_fillColor = newColor;
}

void ShapeMemento::SetOutlineColor(const sf::Color &newColor)
{
  m_outlineColor = newColor;
}

void ShapeMemento::SetThickness(const unsigned int newThickness)
{
  m_thickness = newThickness;
}

void ShapeMemento::SetPosition(const sf::Vector2f &newPosition)
{
  m_position = newPosition;
}
