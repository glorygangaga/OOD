#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

template <typename T>
class SfmlShape
{
public:
  bool ApplyStyle();
  std::shared_ptr<sf::Shape> GetShape() const;

protected:
  std::shared_ptr<T> m_shape;
};

#include "src/Shapes/SFML/SfmlShape.tpp"