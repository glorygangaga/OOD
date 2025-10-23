#pragma once

#include "SfmlShape.hpp"

class SfmlRectangle : public SfmlShape<sf::RectangleShape>
{
public:
  SfmlRectangle(const sf::Vector2f &p1, const sf::Vector2f &p2);
};
