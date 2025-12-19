#pragma once

#include "include/tools/save/IShapeBuilder.hpp"

#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"
#include "include/shapes/CompositeShape.hpp"

class ShapeBuilder : public IShapeBuilder
{
public:
  void Reset() override;

  void SetType(const SHAPES_TYPE &type) override;
  void SetPosition(const sf::Vector2f &position) override;

  void SetCircleData(const sf::Vector2f &center, float radius) override;
  void SetRectangleData(const sf::Vector2f &p1, const sf::Vector2f &p2) override;
  void SetTriangleData(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f &p3) override;
  void SetCompositeData(const std::vector<std::shared_ptr<IDrawableShape>> &children) override;

  void SetOutlneColor(const uint32_t color) override;
  void SetOutlineThickness(const float thickness) override;
  void SetFillColor(const uint32_t color) override;

  std::shared_ptr<IDrawableShape> GetResult() override;
  std::vector<std::shared_ptr<IDrawableShape>> GetUndrawChildren() override;

private:
  SHAPES_TYPE m_type;
  float m_thickness;
  sf::Vector2f m_position;
  uint32_t m_color, m_outlineColor;

  float m_radius;        // circle
  sf::Vector2f m_center; // circle

  sf::Vector2f m_p1, m_p2; // rectangle + triangle
  sf::Vector2f m_p3;       // triangle

  std::vector<std::shared_ptr<IDrawableShape>> m_children;
  std::vector<std::shared_ptr<IDrawableShape>> m_unDrawChildren;
};