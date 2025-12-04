#pragma once

#include <vector>
#include <memory>

#include "include/shapes/SFML/IDrawableShape.hpp"

class CompositeShape : public IDrawableShape
{
public:
  void Add(const std::shared_ptr<IDrawableShape> &shape);

  void Move(const sf::Vector2f &delta) override;
  bool Contains(const sf::Vector2f &point) const override;
  std::shared_ptr<sf::Shape> GetShape() const override;
  double GetArea() const override;
  double GetPerimeter() const override;
  std::string ToString() const override;
  void Accept(IShapeVisitor &visitor) override;
  std::vector<ShapeMemento> SaveState() const override;
  void RestoreState(const std::vector<ShapeMemento> &lastState) override;
  size_t GetStateSize() const override;

  const std::vector<std::shared_ptr<IDrawableShape>> &GetShapes() const;
  std::vector<std::shared_ptr<IDrawableShape>> GetAllShapes();
  void CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes);

  sf::FloatRect GetBounds() const;

private:
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
};
