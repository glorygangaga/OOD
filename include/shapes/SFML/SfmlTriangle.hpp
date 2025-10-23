#pragma once

#include "SfmlShape.hpp"

class SfmlTriangle : public SfmlShape<sf::ConvexShape>
{
public:
  SfmlTriangle(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3);
};
