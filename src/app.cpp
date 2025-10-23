#include "include/app.hpp"

bool Application::Start()
{
  ProcessInput();
  m_canvas.Draw();

  return true;
}

bool Application::ProcessInput()
{
  std::string shapeString;
  while (m_input >> shapeString)
  {
    const auto it = SHAPES_MAP.find(shapeString);
    if (it != SHAPES_MAP.end())
    {
      const auto shape = GetNewShape(it->second);
      PushNewShape(shape);
    }
    else
      return false;
  }

  return true;
}

bool Application::PushNewShape(std::shared_ptr<IDrawableShape> shape)
{
  m_output << shape->ToString();
  m_canvas.PushShape(shape->GetShape());
  return true;
};

std::shared_ptr<IDrawableShape> Application::GetNewShape(const SHAPES_TYPE &shapeType)
{
  switch (shapeType)
  {
  case SHAPES_TYPE::RECTANGLE_T:
    return CreateRectangle();
  case SHAPES_TYPE::TRIANGLE_T:
    return CreateTriangle();
  case SHAPES_TYPE::CIRCLE_T:
    return CreateCircle();
  default:
    return nullptr;
  }
}

std::shared_ptr<RectangleAdapterShape> Application::CreateRectangle()
{
  std::string line;
  unsigned int x1, y1, x2, y2;
  std::getline(m_input, line);
  sscanf(line.c_str(), inputs::RECT_SCAN, &x1, &y1, &x2, &y2);

  return std::make_shared<RectangleAdapterShape>(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2));
}

std::shared_ptr<CircleAdapterShape> Application::CreateCircle()
{
  std::string line;
  unsigned int cx, cy, r;
  std::getline(m_input, line);
  sscanf(line.c_str(), inputs::CIRCLE_SCAN, &cx, &cy, &r);

  return std::make_shared<CircleAdapterShape>(sf::Vector2f(cx, cy), r);
}

std::shared_ptr<TriangleAdapterShape> Application::CreateTriangle()
{
  std::string line;
  unsigned int x1, y1, x2, y2, x3, y3;
  std::getline(m_input, line);
  sscanf(line.c_str(), inputs::TRIANGLE_SCAN, &x1, &y1, &x2, &y2, &x3, &y3);

  return std::make_shared<TriangleAdapterShape>(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2), sf::Vector2f(x3, y3));
}
