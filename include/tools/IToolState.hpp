#pragma once

class IToolState
{
public:
  virtual ~IToolState() = default;
  virtual void HandleEvent(CCanvas *canvas, const sf::Event &event) = 0;
};
