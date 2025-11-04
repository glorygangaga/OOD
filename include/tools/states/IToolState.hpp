#pragma once

#include <SFML/Graphics.hpp>

class CCanvas;

class IToolState
{
public:
  virtual ~IToolState() = default;
  virtual void HandleEvent(CCanvas *canvas, const sf::Event &event) = 0;
};
