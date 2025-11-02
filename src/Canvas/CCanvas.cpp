#include "include/CCanvas.hpp"

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
  if (event.type == sf::Event::KeyPressed)
  {
    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
    sf::Vector2f mousePos = m_window.mapPixelToCoords(pixelPos);

    std::shared_ptr<IDrawableShape> newShape;
    if (event.key.code == sf::Keyboard::Num1)
      newShape = std::make_shared<CircleAdapterShape>(mousePos, 50);
    else if (event.key.code == sf::Keyboard::Num2)
    {
      const sf::Vector2f mousePosP2(mousePos.x, mousePos.y + 100);
      const sf::Vector2f mousePosP3(mousePos.x + 100, mousePos.y + 50);
      newShape = std::make_shared<TriangleAdapterShape>(mousePos, mousePosP2, mousePosP3);
    }
    else if (event.key.code == sf::Keyboard::Num3)
    {
      const sf::Vector2f mousePosP2(mousePos.x + 100, mousePos.y + 100);
      newShape = std::make_shared<RectangleAdapterShape>(mousePos, mousePosP2);
    }
    else
      return;

    m_shapes.push_back(newShape);
  }
}

void CCanvas::ChangeShape(const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed && !m_selected.empty() && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
  {
    if (event.key.code == sf::Keyboard::C)
      for (auto s : m_selected)
      {
        const sf::Color shapeColor = s->GetShape()->getFillColor();
        s->GetShape()->setFillColor(GetNextColor(shapeColor));
      }
    else if (event.key.code == sf::Keyboard::X)
      for (auto s : m_selected)
      {
        const sf::Color shapeColor = s->GetShape()->getOutlineColor();
        s->GetShape()->setOutlineColor(GetNextColor(shapeColor));
      }
    else if (event.key.code == sf::Keyboard::Up)
      for (auto s : m_selected)
      {
        const float thikness = s->GetShape()->getOutlineThickness();
        s->GetShape()->setOutlineThickness(thikness + 1.0f);
      }
    else if (event.key.code == sf::Keyboard::Down)
      for (auto s : m_selected)
      {
        const float thikness = s->GetShape()->getOutlineThickness();
        if (thikness - 1 >= 0)
          s->GetShape()->setOutlineThickness(thikness - 1.0f);
      }
  }
}

bool CCanvas::Render()
{
  m_window.clear(sf::Color::Black);

  for (auto &shape : m_shapes)
  {
    auto drawable = shape->GetShape();
    if (drawable)
      m_window.draw(*drawable);
  }

  for (auto &s : m_selected)
  {
    auto drawable = s->GetShape();
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
    sf::Vector2f clickPos = m_window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
    auto hit = hitTest(clickPos);

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
      for (auto &s : m_selected)
      {
        group->Add(s);
      }
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
          for (auto &child : g->GetShapes())
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

    for (auto &s : m_selected)
      s->Move(delta);

    m_lastMousePos = currPos;
  }
}

sf::Color CCanvas::GetNextColor(const sf::Color &colorShape) const
{
  int current = static_cast<int>(GetEnumFromColor(colorShape));
  int next = (current + 1) % SHAPE_COLORS_SIZE;

  SHAPE_COLORS nextColorEnum = static_cast<SHAPE_COLORS>(next);
  const auto it = COLORS_MAP.find(nextColorEnum);
  if (it == COLORS_MAP.end())
    return sf::Color::Transparent;

  return it->second;
}

SHAPE_COLORS CCanvas::GetEnumFromColor(const sf::Color &color) const
{
  for (const auto &pair : COLORS_MAP)
  {
    if (pair.second == color)
      return pair.first;
  }
  return SHAPE_COLORS::BLACK;
}

std::shared_ptr<IDrawableShape> CCanvas::hitTest(const sf::Vector2f &point) const
{
  for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
  {
    const sf::FloatRect bounds = (*it)->GetShape()->getGlobalBounds();
    if (bounds.contains(point))
      return *it;
  }

  return nullptr;
}
