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

    if (event.type == sf::Event::MouseMoved && m_dragging)
    {
      sf::Vector2f currPos = m_window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y});
      sf::Vector2f delta = currPos - m_lastMousePos;

      for (auto &s : m_selected)
        s->Move(delta);

      m_lastMousePos = currPos;
    }

    if (event.type == sf::Event::KeyPressed)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
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
  }

  return true;
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

std::shared_ptr<IDrawableShape> CCanvas::hitTest(const sf::Vector2f &point)
{
  for (auto it = m_shapes.rbegin(); it != m_shapes.rend(); ++it)
  {
    const sf::FloatRect bounds = (*it)->GetShape()->getGlobalBounds();
    if (bounds.contains(point))
      return *it;
  }

  return nullptr;
}
