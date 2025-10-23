#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "include/shapes/CompositeShape.hpp"

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
  bool Render();

  std::shared_ptr<IDrawableShape> hitTest(const sf::Vector2f &point);
};
