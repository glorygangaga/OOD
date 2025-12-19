#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include "include/shapes/IShape.hpp"
#include "include/shapes/Visitor/IShapeVisitor.hpp"
#include "include/shapes/ShapeMemento.hpp"

class IDrawableShape : public IShape
{
public:
  IDrawableShape() : m_id(++s_nextId) {}

  virtual std::shared_ptr<sf::Shape> GetShape() const = 0;
  virtual bool Contains(const sf::Vector2f &point) const = 0;
  virtual void Move(const sf::Vector2f &delta) = 0;
  virtual void Accept(IShapeVisitor &visitor) = 0;

  virtual std::vector<ShapeMemento> SaveState() const = 0;
  virtual void RestoreState(const std::vector<ShapeMemento> &lastState) = 0;

  virtual size_t GetStateSize() const = 0;

  unsigned int GetId() const { return m_id; }
  bool InGroup() { return inGroup; }
  void SetInGroup(const bool group) { inGroup = group; }

  virtual void SerializeToBinary(std::ostream &out) const = 0;
  virtual void SerializeToText(std::ostream &out) const = 0;

private:
  unsigned int m_id;
  bool inGroup;
  inline static unsigned int s_nextId = 0;
};
