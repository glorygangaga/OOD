#include "include/CCanvas.hpp"
#include "include/tools/states/DragState.hpp"
#include "include/tools/states/AddShapeState.hpp"

CCanvas::CCanvas(const unsigned int width, const unsigned int height, const std::string &titleName)
    : m_window(sf::VideoMode(width, height), titleName), m_panel(m_window, [this](std::unique_ptr<IToolState> tool)
                                                                 { this->SetTool(std::move(tool)); })
{
  m_window.setFramerateLimit(60);
};

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

bool CCanvas::RemoveShape(const std::shared_ptr<IDrawableShape> &shape)
{
  if (m_shapes.empty())
    return false;

  std::vector<std::shared_ptr<IDrawableShape>>::iterator pos = std::find(m_shapes.begin(), m_shapes.end(), shape);
  if (pos != m_shapes.end())
  {
    m_shapes.erase(pos);
    return true;
  }

  return false;
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
    SetEvent(event);
    SelectEvent(event);
    m_panel.HandleMouseEvent(event);

    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && event.key.code == sf::Keyboard::Z && !cmds.empty())
    {
      auto cmd = std::move(cmds.back());
      cmds.pop_back();

      ClearSelected();
      cmd->Undo();
    }

    if (m_tool)
    {
      m_tool->HandleEvent(this);
      if (!m_panel.IsDragMode())
        SetTool(nullptr);
    }
  }

  return true;
}

void CCanvas::SelectEvent(const sf::Event &event)
{
  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
  {
    sf::Vector2f clickPos = GetMousePosition();
    bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    auto hit = hitTest(clickPos);
    const sf::Vector2f panelSize = m_panel.GetPanelSize();

    if (clickPos.y <= panelSize.y)
      return;

    if (hit)
    {
      if (!shift)
        ClearSelected();

      SelectShape(hit);
      StartDragging(clickPos);
    }
    else if (!shift)
      ClearSelected();
  }

  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    StopDragging();
}

std::vector<std::shared_ptr<IDrawableShape>> CCanvas::GetAllSelectedShapes()
{
  auto shapes = GetSelected();
  std::vector<std::shared_ptr<IDrawableShape>> result;

  for (const auto &s : shapes)
    CollectShapes(s, result);
  return result;
}

void CCanvas::CollectShapes(const std::shared_ptr<IDrawableShape> &shape, std::vector<std::shared_ptr<IDrawableShape>> &outShapes)
{
  auto group = std::dynamic_pointer_cast<CompositeShape>(shape);
  if (group)
    for (const auto &s : group->GetShapes())
      CollectShapes(s, outShapes);
  else
    outShapes.push_back(shape);
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
  m_panel.DrawPanel();
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

void CCanvas::ExecuteCommand(std::unique_ptr<ICommand> cmd)
{
  cmd->Execute();
  cmds.push_back(std::move(cmd));
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

std::shared_ptr<CompositeShape> CCanvas::GroupShapes(const std::vector<std::shared_ptr<IDrawableShape>> &shapes)
{
  auto group = std::make_shared<CompositeShape>();
  for (const auto &s : shapes)
  {
    group->Add(s);
  }

  m_shapes.push_back(group);
  m_selected.clear();
  m_selected.push_back(group);
  return group;
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

void CCanvas::UngroupShapes(const std::vector<std::shared_ptr<IDrawableShape>> &shapes)
{
  std::vector<std::shared_ptr<IDrawableShape>> toAdd;
  for (auto &s : shapes)
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

sf::Event CCanvas::GetEvent() const
{
  return m_event;
}

void CCanvas::SetEvent(const sf::Event &event)
{
  m_event = event;
}