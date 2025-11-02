#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include "include/shapes/CompositeShape.hpp"

#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"

class CCanvas
{
public:
  CCanvas(const unsigned int width, const unsigned int height, const std::string &titleName)
      : m_window(sf::VideoMode(width, height), titleName) {};

  bool Draw();
  bool PushShape(const std::shared_ptr<IDrawableShape> &shape);
  bool IsOpen() const;

private:
  sf::RenderWindow m_window;
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
  std::vector<std::shared_ptr<IDrawableShape>> m_selected;
  bool m_dragging = false;
  sf::Vector2f m_lastMousePos;

  bool HandleEvents();

  void AddNewShape(const sf::Event &event);
  void HandleMouseDragEvent(const sf::Event &event);
  void HandleGroupEvent(const sf::Event &event);
  void HandleDragEvent(const sf::Event &event);
  void ChangeShape(const sf::Event &event);
  bool Render();

  sf::Color GetNextColor(const sf::Color &colorShape) const;
  SHAPE_COLORS GetEnumFromColor(const sf::Color &color) const;
  std::shared_ptr<IDrawableShape> hitTest(const sf::Vector2f &point) const;
};
