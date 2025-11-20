#pragma once

#include <vector>

#include "include/ui/button/Button.hpp"
#include "include/Constants.hpp"

#include "include/tools/states/IToolState.hpp"

class Panel
{
public:
  Panel(sf::RenderWindow &window, std::function<void(std::unique_ptr<IToolState>)> setTool);

  void DrawPanel();
  void HandleMouseEvent(const sf::Event &event);
  bool IsDragMode() const;
  sf::Vector2f GetPanelSize() const;

private:
  std::vector<Button> m_buttons;
  sf::RenderWindow &m_window;
  sf::Font m_font;
  std::function<void(std::unique_ptr<IToolState>)> m_setTool;
  bool m_dragMode = false;
  sf::RectangleShape m_rectPanel;

  void SetPanel();
  std::unique_ptr<IToolState> GetState(const enum Action &action);
};
