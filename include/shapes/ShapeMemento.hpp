#pragma once

#include <SFML/Graphics.hpp>

class ShapeMemento
{
public:
  sf::Color GetFillColor() const;
  sf::Color GetOutlineColor() const;
  unsigned int GetThickness() const;
  sf::Transform GetTransform() const;

  void SetFillColor(const sf::Color &newColor);
  void SetOutlineColor(const sf::Color &newColor);
  void SetThickness(const unsigned int newThickness);
  void SetTransform(const sf::Transform &newTransform);

private:
  sf::Color m_fillColor;
  sf::Color m_outlineColor;
  unsigned int m_thickness;
  sf::Transform m_transform;
};
