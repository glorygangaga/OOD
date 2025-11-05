#include "include/CCanvas.hpp"
#include "include/tools/states/ChangeColorShapeState.hpp"
#include "include/tools/states/AddShapeState.hpp"
#include "include/tools/states/ChangeThicknessShapeState.hpp"
#include "include/tools/states/DragState.hpp"

bool CCanvas::Draw()
{
  while (IsOpen())
  {
    HandleEvents();
    Render();
  }

  return true;
}

bool CCanvas::PushShape(const std::shared_ptr<IDrawableShape> &shape)
{
  m_shapes.push_back(shape);
  return true;
}

bool CCanvas::IsOpen() const
{
  return m_window.isOpen();
}

sf::Vector2f CCanvas::GetMousePosition() const
{
  sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
  return m_window.mapPixelToCoords(pixelPos);
}

bool CCanvas::HandleEvents()
{
  sf::Event event;
  while (m_window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
      m_window.close();

    ChangeMode(event);
    AddNewShape(event);
    switch (m_mode)
    {
    case MODE::SHAPE_CHANGE:
      ChangeShape(event);
      break;
    case MODE::DND:
      if (!dynamic_cast<DragState *>(m_tool.get()))
        SetTool(std::make_unique<DragState>());
      break;
    }

    if (m_tool)
      m_tool->HandleEvent(this, event);
  }

  return true;
}

void CCanvas::ChangeMode(const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::V)
  {
    const int current = static_cast<int>(m_mode);
    const int next = (current + 1) % MODE_SIZE;
    m_mode = static_cast<MODE>(next);

    switch (m_mode)
    {
    case MODE::SHAPE_CHANGE:
      ClearSelected();
      ClearTool();
      break;
    case MODE::DND:
      SetTool(std::make_unique<DragState>());
      break;
    }
  }
}

void CCanvas::AddNewShape(const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed &&
      (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Num3))
  {
    SetTool(std::make_unique<AddShapeState>());
    if (m_tool)
      m_tool->HandleEvent(this, event);
  }
}

void CCanvas::ChangeShape(const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
  {
    if (event.key.code == sf::Keyboard::C || event.key.code == sf::Keyboard::X)
      SetTool(std::make_unique<ChangeColorShapeState>());
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
      SetTool(std::make_unique<ChangeThicknessShapeState>());
  }
}

bool CCanvas::Render()
{
  m_window.clear(sf::Color::Black);

  for (const auto &shape : m_shapes)
  {
    const auto drawable = shape->GetShape();
    if (drawable)
      m_window.draw(*drawable);
  }

  for (const auto &s : m_selected)
  {
    const auto drawable = s->GetShape();
    if (!drawable)
      continue;

    const sf::FloatRect bounds = drawable->getGlobalBounds();
    const sf::RectangleShape frame = RenderFrame(bounds);
    m_window.draw(frame);
  }

  m_window.display();

  return true;
}

sf::RectangleShape CCanvas::RenderFrame(const sf::FloatRect &bounds) const
{
  sf::RectangleShape frame({bounds.width, bounds.height});
  frame.setPosition(bounds.left, bounds.top);
  frame.setFillColor(sf::Color::Transparent);
  frame.setOutlineThickness(window::frame_thickness);
  frame.setOutlineColor(sf::Color::Yellow);
  return frame;
}

std::shared_ptr<IDrawableShape> CCanvas::hitTest(const sf::Vector2f &point) const
{
  if (m_shapes.empty())
    return nullptr;

  for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
  {
    const sf::FloatRect bounds = (*it)->GetShape()->getGlobalBounds();
    if (bounds.contains(point))
      return *it;
  }

  return nullptr;
}

std::shared_ptr<IDrawableShape> CCanvas::GetShapeByHit(const sf::Vector2f &point) const
{
  if (m_shapes.empty())
    return nullptr;

  for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
  {
    auto shape = *it;

    auto group = std::dynamic_pointer_cast<CompositeShape>(shape);
    if (group)
    {
      for (auto rit = group->GetShapes().rbegin(); rit != group->GetShapes().rend(); ++rit)
      {
        if ((*rit)->GetShape()->getGlobalBounds().contains(point))
          return *rit;
      }
      if (shape->Contains(point))
        return shape;
    }
    else if (shape->Contains(point))
      return shape;
  }

  return nullptr;
}

void CCanvas::ExecuteCommand(std::unique_ptr<ICommand> cmd)
{
  cmd->Execute();
}

void CCanvas::SetTool(std::unique_ptr<IToolState> tool)
{
  m_tool = std::move(tool);
}

void CCanvas::ClearTool()
{
  m_tool = nullptr;
}

void CCanvas::SelectShape(const std::shared_ptr<IDrawableShape> &shape)
{
  if (std::find(m_selected.begin(), m_selected.end(), shape) == m_selected.end())
    m_selected.push_back(shape);
}

std::vector<std::shared_ptr<IDrawableShape>> CCanvas::GetSelected() const
{
  return m_selected;
}

void CCanvas::ClearSelected()
{
  m_selected.clear();
}

void CCanvas::StartDragging(const sf::Vector2f &pos)
{
  m_dragging = true;
  m_lastMousePos = pos;
}

void CCanvas::StopDragging()
{
  m_dragging = false;
}

bool CCanvas::IsDragging() const
{
  return m_dragging;
}

void CCanvas::SetLastMousePos(const sf::Vector2f &pos)
{
  m_lastMousePos = pos;
}

sf::Vector2f CCanvas::GetLastMousePos() const
{
  return m_lastMousePos;
}

void CCanvas::GroupSelected()
{
  auto group = std::make_shared<CompositeShape>();
  for (const auto &s : m_selected)
    group->Add(s);

  m_shapes.push_back(group);
  m_selected.clear();
  m_selected.push_back(group);
}

void CCanvas::UngroupSelected()
{
  std::vector<std::shared_ptr<IDrawableShape>> toAdd;
  for (auto &s : m_selected)
  {
    auto g = std::dynamic_pointer_cast<CompositeShape>(s);
    if (g)
    {
      for (auto &child : g->GetShapes())
        toAdd.push_back(child);
      m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), s), m_shapes.end());
    }
  }
  m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());
  m_selected = toAdd;
}
