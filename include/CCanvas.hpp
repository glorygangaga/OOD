#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>

#include "include/tools/commands/ICommand.hpp"
#include "include/tools/states/IToolState.hpp"

#include "include/shapes/CompositeShape.hpp"

class CCanvas
{
public:
  CCanvas(const unsigned int width, const unsigned int height, const std::string &titleName)
      : m_window(sf::VideoMode(width, height), titleName) {};

  bool Draw();
  bool PushShape(const std::shared_ptr<IDrawableShape> &shape);
  bool IsOpen() const;

  sf::Vector2f GetMousePosition() const;
  std::shared_ptr<IDrawableShape> GetShapeByHit(const sf::Vector2f &point) const;
  void ExecuteCommand(std::unique_ptr<ICommand> cmd);
  void SetTool(std::unique_ptr<IToolState> tool);

private:
  sf::RenderWindow m_window;
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
  std::vector<std::shared_ptr<IDrawableShape>> m_selected;
  bool m_dragging = false;
  sf::Vector2f m_lastMousePos;
  std::unique_ptr<IToolState> m_tool;

  bool HandleEvents();

  std::shared_ptr<IDrawableShape> hitTest(const sf::Vector2f &point) const;
  void AddNewShape(const sf::Event &event);
  void HandleMouseDragEvent(const sf::Event &event);
  void HandleGroupEvent(const sf::Event &event);
  void HandleDragEvent(const sf::Event &event);
  void ChangeShape(const sf::Event &event);
  bool Render();
};
