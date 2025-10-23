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

bool CCanvas::PushShape(const std::shared_ptr<sf::Shape> &shape)
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
  }

  return true;
}

bool CCanvas::Render()
{
  m_window.clear(sf::Color::Black);
  for (const auto &shape : m_shapes)
    m_window.draw(*shape);
  m_window.display();

  return true;
}
