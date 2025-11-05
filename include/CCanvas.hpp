#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

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
  std::shared_ptr<IDrawableShape> hitTest(const sf::Vector2f &point) const;
  std::shared_ptr<IDrawableShape> GetShapeByHit(const sf::Vector2f &point) const;
  void ExecuteCommand(std::unique_ptr<ICommand> cmd);

  void ClearSelected();
  void StartDragging(const sf::Vector2f &pos);
  void StopDragging();
  bool IsDragging() const;
  void SetLastMousePos(const sf::Vector2f &pos);
  sf::Vector2f GetLastMousePos() const;
  void GroupSelected();
  void UngroupSelected();
  void SelectShape(const std::shared_ptr<IDrawableShape> &shape);
  std::vector<std::shared_ptr<IDrawableShape>> GetSelected() const;

private:
  sf::RenderWindow m_window;
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
  std::vector<std::shared_ptr<IDrawableShape>> m_selected;
  bool m_dragging = false;
  sf::Vector2f m_lastMousePos;
  std::unique_ptr<IToolState> m_tool;
  MODE m_mode = MODE::DND;

  bool HandleEvents();

  void SetTool(std::unique_ptr<IToolState> tool);
  void ClearTool();
  void AddNewShape(const sf::Event &event);
  void ChangeShape(const sf::Event &event);
  void ChangeMode(const sf::Event &event);
  bool Render();

  sf::RectangleShape RenderFrame(const sf::FloatRect &bounds) const;
};
