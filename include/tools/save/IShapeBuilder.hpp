#pragma once

#include <memory>
#include "include/shapes/SFML/IDrawableShape.hpp"

class IShapeBuilder
{
public:
  virtual void Reset() = 0;

  virtual void SetType(const SHAPES_TYPE &type) = 0;
  virtual void SetPosition(const sf::Vector2f &position) = 0;

  virtual void SetCircleData(const sf::Vector2f &center, float radius) = 0;
  virtual void SetRectangleData(const sf::Vector2f &p1, const sf::Vector2f &p2) = 0;
  virtual void SetTriangleData(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3) = 0;
  virtual void SetCompositeData(const std::vector<std::shared_ptr<IDrawableShape>> &children) = 0;

  virtual void SetOutlneColor(const uint32_t color) = 0;
  virtual void SetOutlineThickness(const float thickness) = 0;
  virtual void SetFillColor(const uint32_t color) = 0;

  virtual std::shared_ptr<IDrawableShape> GetResult() = 0;

  virtual std::vector<std::shared_ptr<IDrawableShape>> GetUndrawChildren() = 0;
};
