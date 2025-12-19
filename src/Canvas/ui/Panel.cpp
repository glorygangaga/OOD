#include "include/ui/Panel.hpp"

#include "include/tools/states/ChangeColorShapeState.hpp"
#include "include/tools/states/AddShapeState.hpp"
#include "include/tools/states/ChangeThicknessShapeState.hpp"
#include "include/tools/states/DragState.hpp"
#include "include/tools/states/ChangeColorThickness.hpp"
#include "include/tools/states/LoadBinState.hpp"
#include "include/tools/states/LoadTxtState.hpp"

Panel::Panel(sf::RenderWindow &window, std::function<void(std::unique_ptr<IToolState>)> setTool)
    : m_window(window), m_setTool(setTool)
{
  m_font.loadFromFile(inputs::FONT_FILENAME);
  SetPanel();
}

void Panel::SetPanel()
{
  sf::Vector2f buttonPos = sf::Vector2f(0, 0);
  const sf::Vector2f buttonSize = sf::Vector2f(100, 30);

  for (const auto &pair : BUTTONS)
  {
    Button btn(buttonPos, buttonSize, pair.first, m_font, pair.second);
    btn.onClick = [this, action = pair.second]()
    {
      std::unique_ptr<IToolState> state = GetState(action);
      if (state)
        m_setTool(std::move(state));
    };
    m_buttons.push_back(btn);

    if (buttonPos.x + 220 >= static_cast<float>(window::SIZE))
    {
      buttonPos.x = 0;
      buttonPos.y += 40;
    }
    else
      buttonPos.x += 110;
  }

  m_rectPanel.setPosition(sf::Vector2f(0, 0));
  m_rectPanel.setSize(sf::Vector2f(window::SIZE, buttonPos.y + buttonSize.y + 20));
  m_rectPanel.setFillColor(sf::Color(128, 128, 128));
}

void Panel::DrawPanel()
{
  m_window.draw(m_rectPanel);
  for (const Button &btn : m_buttons)
  {
    if (m_dragMode)
    {
      if (btn.GetAction() == Action::SwitchMode)
        btn.Draw(m_window);
    }
    else
      btn.Draw(m_window);
  }
}

void Panel::HandleMouseEvent(const sf::Event &event)
{
  for (auto &btn : m_buttons)
    if (btn.IsClicked(m_window, event))
      if (btn.onClick)
        btn.onClick();
}

std::unique_ptr<IToolState> Panel::GetState(const enum Action &action)
{
  if (action == Action::SwitchMode)
  {
    m_dragMode = !m_dragMode;
    if (m_dragMode)
      return std::make_unique<DragState>(GetPanelSize());
    else
      return nullptr;
  }

  if (m_dragMode)
    return std::make_unique<DragState>(GetPanelSize());

  switch (action)
  {
  case Action::ColorBlack:
    return std::make_unique<ChangeColorShapeState>(sf::Color::Black);
  case Action::ColorBlue:
    return std::make_unique<ChangeColorShapeState>(sf::Color::Blue);
  case Action::ColorRed:
    return std::make_unique<ChangeColorShapeState>(sf::Color::Red);
  case Action::ColorWhite:
    return std::make_unique<ChangeColorShapeState>(sf::Color::White);
  case Action::Thick1:
    return std::make_unique<ChangeThicknessShapeState>(1);
  case Action::Thick3:
    return std::make_unique<ChangeThicknessShapeState>(3);
  case Action::Thick5:
    return std::make_unique<ChangeThicknessShapeState>(5);
  case Action::FillColorBlack:
    return std::make_unique<ChangeColorThickness>(sf::Color::Black);
  case Action::FillColorBlue:
    return std::make_unique<ChangeColorThickness>(sf::Color::Blue);
  case Action::FillColorRed:
    return std::make_unique<ChangeColorThickness>(sf::Color::Red);
  case Action::FillColorWhite:
    return std::make_unique<ChangeColorThickness>(sf::Color::White);
  case Action::AddCircle:
    return std::make_unique<AddShapeState>(SHAPES_TYPE::CIRCLE_T, GetPanelSize());
  case Action::AddRectangle:
    return std::make_unique<AddShapeState>(SHAPES_TYPE::RECTANGLE_T, GetPanelSize());
  case Action::AddTriangle:
    return std::make_unique<AddShapeState>(SHAPES_TYPE::TRIANGLE_T, GetPanelSize());
  case Action::LoadLastShapesBin:
    return std::make_unique<LoadBinState>();
  case Action::LoadLastShapesTxt:
    return std::make_unique<LoadTxtState>();
  default:
    return nullptr;
  }
}

bool Panel::IsDragMode() const
{
  return m_dragMode;
}

sf::Vector2f Panel::GetPanelSize() const
{
  return m_rectPanel.getSize();
}
