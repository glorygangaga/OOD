#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class CCanvas
{
public:
  CCanvas(const unsigned int width, const unsigned int height, const std::string &titleName)
      : m_window(sf::VideoMode(width, height), titleName) {};

  bool Draw();
  bool PushShape(const std::shared_ptr<sf::Shape> &shape);
  bool IsOpen() const;

private:
  sf::RenderWindow m_window;
  std::vector<std::shared_ptr<sf::Shape>> m_shapes;

  bool HandleEvents();
  bool Render();
};
