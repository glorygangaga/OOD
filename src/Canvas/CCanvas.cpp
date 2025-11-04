#include "include/CCanvas.hpp"
#include "include/tools/states/ChangeColorShapeState.hpp"
#include "include/tools/states/AddShapeState.hpp"
#include "include/tools/states/ChangeThicknessShapeState.hpp"

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

    HandleMouseDragEvent(event);
    HandleDragEvent(event);
    HandleGroupEvent(event);
    AddNewShape(event);
    ChangeShape(event);
  }

  return true;
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
    {
      SetTool(std::make_unique<ChangeColorShapeState>());
      if (m_tool)
        m_tool->HandleEvent(this, event);
    }
    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
    {
      SetTool(std::make_unique<ChangeThicknessShapeState>());
      if (m_tool)
        m_tool->HandleEvent(this, event);
    }
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

    sf::FloatRect bounds = drawable->getGlobalBounds();
    sf::RectangleShape frame({bounds.width, bounds.height});
    frame.setPosition(bounds.left, bounds.top);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(2.f);
    frame.setOutlineColor(sf::Color::Yellow);
    m_window.draw(frame);
  }

  m_window.display();

  return true;
}

void CCanvas::HandleMouseDragEvent(const sf::Event &event)
{
  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
  {
    const sf::Vector2f clickPos = m_window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    const bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    const auto hit = hitTest(clickPos);

    if (hit)
    {
      if (!shift)
        m_selected.clear();

      if (std::find(m_selected.begin(), m_selected.end(), hit) == m_selected.end())
        m_selected.push_back(hit);

      m_dragging = true;
      m_lastMousePos = clickPos;
    }
    else if (!shift)
      m_selected.clear();
  }

  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    m_dragging = false;
}

void CCanvas::HandleGroupEvent(const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
  {
    if (event.key.code == sf::Keyboard::G)
    {
      auto group = std::make_shared<CompositeShape>();
      for (const auto &s : m_selected)
        group->Add(s);
      m_shapes.push_back(group);
      m_selected.clear();
      m_selected.push_back(group);
    }

    if (event.key.code == sf::Keyboard::U)
    {
      std::vector<std::shared_ptr<IDrawableShape>> toAdd;
      for (auto &s : m_selected)
      {
        auto g = std::dynamic_pointer_cast<CompositeShape>(s);
        if (g)
        {
          for (const auto &child : g->GetShapes())
            toAdd.push_back(child);
          m_shapes.erase(std::remove(m_shapes.begin(), m_shapes.end(), s), m_shapes.end());
        }
      }
      m_shapes.insert(m_shapes.end(), toAdd.begin(), toAdd.end());
      m_selected = toAdd;
    }
  }
}

void CCanvas::HandleDragEvent(const sf::Event &event)
{
  if (event.type == sf::Event::MouseMoved && m_dragging)
  {
    sf::Vector2f currPos = m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
    sf::Vector2f delta = currPos - m_lastMousePos;

    for (const auto &s : m_selected)
      s->Move(delta);

    m_lastMousePos = currPos;
  }
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
  for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
  {
    auto shape = *it;

    auto group = std::dynamic_pointer_cast<CompositeShape>(shape);
    if (group)
    {
      for (auto rit = group->GetShapes().rbegin(); rit != group->GetShapes().rend(); ++rit)
      {
        if ((*rit)->Contains(point))
          return *rit;
      }
      if (shape->Contains(point))
        return shape;
    }
    else
    {
      if (shape->Contains(point))
        return shape;
    }
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
