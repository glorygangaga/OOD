#pragma once

#include <SFML/Graphics.hpp>

class ShapeMemento
{
public:
  sf::Color GetFillColor() const;
  sf::Color GetOutlineColor() const;
  unsigned int GetThickness() const;
  sf::Vector2f GetPosition() const;

  void SetFillColor(const sf::Color &newColor);
  void SetOutlineColor(const sf::Color &newColor);
  void SetThickness(const unsigned int newThickness);
  void SetPosition(const sf::Vector2f &newPosition);

private:
  sf::Color m_fillColor;
  sf::Color m_outlineColor;
  unsigned int m_thickness;
  sf::Vector2f m_position;
};
