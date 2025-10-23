#pragma once

template <typename T>
bool SfmlShape<T>::ApplyStyle()
{
  if (!m_shape)
    return false;

  m_shape->setFillColor(sf::Color::Transparent);
  m_shape->setOutlineColor(sf::Color::Red);
  m_shape->setOutlineThickness(2);
  return true;
}

template <typename T>
std::shared_ptr<sf::Shape> SfmlShape<T>::GetShape() const
{
  return m_shape;
};
