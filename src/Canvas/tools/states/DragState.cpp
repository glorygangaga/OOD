#include "include/tools/states/DragState.hpp"

void DragState::HandleEvent(CCanvas *canvas)
{
  const sf::Event event = canvas->GetEvent();

  if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    canvas->StopDragging();

  if (event.type == sf::Event::MouseMoved && canvas->IsDragging())
  {
    sf::Vector2f currPos = canvas->GetMousePosition();
    sf::Vector2f delta = currPos - canvas->GetLastMousePos();

    for (const auto &s : canvas->GetSelected())
    {
      const sf::FloatRect bounds = s->GetShape()->getGlobalBounds();

      if (bounds.top + delta.y <= m_startPos.y || bounds.top + delta.y + bounds.height >= window::SIZE)
        delta.y = 0;
      if (bounds.left + delta.x <= 0 || bounds.left + delta.x + bounds.width >= window::SIZE)
        delta.x = 0;

      canvas->ExecuteCommand(std::make_unique<DragCommand>(s, delta));
    }

    canvas->SetLastMousePos(currPos);
  }

  if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
  {
    if (event.key.code == sf::Keyboard::G)
      canvas->GroupSelected();
    if (event.key.code == sf::Keyboard::U)
      canvas->UngroupSelected();
  }
}