#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "include/tools/commands/ICommand.hpp"
#include "include/tools/states/IToolState.hpp"

#include "include/shapes/CompositeShape.hpp"
#include "include/ui/Panel.hpp"

class CCanvas
{
public:
  CCanvas(const unsigned int width, const unsigned int height, const std::string &titleName);

  bool Draw();
  bool IsOpen() const;
  bool IsDragging() const;
  bool PushShape(const std::shared_ptr<IDrawableShape> &shape);
  bool RemoveShape(const std::shared_ptr<IDrawableShape> &shape);

  sf::Event GetEvent() const;
  sf::Vector2f GetMousePosition() const;
  sf::Vector2f GetLastMousePos() const;
  std::vector<std::shared_ptr<IDrawableShape>> GetSelected() const;
  std::vector<std::shared_ptr<IDrawableShape>> GetAllSelectedShapes();
  void ExecuteCommand(std::unique_ptr<ICommand> cmd);

  void StopDragging();
  void GroupSelected();
  std::shared_ptr<CompositeShape> GroupShapes(const std::vector<std::shared_ptr<IDrawableShape>> &shapes);
  void UngroupSelected();
  void UngroupShapes(const std::vector<std::shared_ptr<IDrawableShape>> &shapes);
  void SetLastMousePos(const sf::Vector2f &pos);

private:
  Panel m_panel;
  sf::Event m_event;
  bool m_dragging = false;
  sf::RenderWindow m_window;
  sf::Vector2f m_lastMousePos;
  std::unique_ptr<IToolState> m_tool;
  std::vector<std::shared_ptr<IDrawableShape>> m_shapes;
  std::vector<std::shared_ptr<IDrawableShape>> m_selected;
  std::vector<std::unique_ptr<ICommand>> cmds;

  bool HandleEvents();
  void ClearTool();
  bool Render();

  void ClearSelected();
  void SetEvent(const sf::Event &event);
  void SelectEvent(const sf::Event &event);
  void StartDragging(const sf::Vector2f &pos);
  void SetTool(std::unique_ptr<IToolState> tool);
  void SelectShape(const std::shared_ptr<IDrawableShape> &shape);
  sf::RectangleShape RenderFrame(const sf::FloatRect &bounds) const;
  std::shared_ptr<IDrawableShape> hitTest(const sf::Vector2f &point) const;
  void CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes);
};
