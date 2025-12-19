#include "include/tools/save/TxtShapeLoader.hpp"
#include <iostream>

void TxtShapeLoader::BeginOpen(const std::string &filename)
{
  m_filename = filename;
  m_file.open(filename);

  m_file >> m_remaining;
}

void TxtShapeLoader::ReadType()
{
  std::string type;
  m_file >> type;

  const auto it = SHAPES_MAP.find(type);
  if (it != SHAPES_MAP.end())
  {
    builder.SetType(it->second);
    m_type = it->second;
  }
}

void TxtShapeLoader::ReadPosition()
{
  if (m_type != SHAPES_TYPE::NONE && m_type != SHAPES_TYPE::COMPOSITE_T)
  {
    float x, y;
    m_file >> x >> y;
    builder.SetPosition({x, y});
  }
}

void TxtShapeLoader::ReadExtra()
{
  switch (m_type)
  {
  case SHAPES_TYPE::CIRCLE_T:
  {
    float x, y, radius;
    m_file >> x >> y >> radius;
    builder.SetCircleData({x, y}, radius);
    break;
  }
  case SHAPES_TYPE::RECTANGLE_T:
  {
    float x1, y1, x2, y2;
    m_file >> x1 >> y1 >> x2 >> y2;
    builder.SetRectangleData({x1, y1}, {x2, y2});
    break;
  }
  case SHAPES_TYPE::TRIANGLE_T:
  {
    float x1, y1, x2, y2, x3, y3;
    m_file >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    builder.SetTriangleData({x1, y1}, {x2, y2}, {x3, y3});
    break;
  }
  case SHAPES_TYPE::COMPOSITE_T:
  {
    uint32_t size;
    m_file >> size;

    std::vector<std::shared_ptr<IDrawableShape>> shapes;
    for (uint32_t i = 0; i < size; i++)
    {
      auto shape = LoadShape();
      shapes.push_back(shape);
    }

    builder.SetCompositeData(shapes);
    builder.SetType(SHAPES_TYPE::COMPOSITE_T);

    m_remaining--;
    return;
  }
  default:
    return;
  }

  uint32_t outlineColor;
  m_file >> outlineColor;
  builder.SetOutlneColor(outlineColor);

  float thickness;
  m_file >> thickness;
  builder.SetOutlineThickness(thickness);

  uint32_t fillColor;
  m_file >> fillColor;
  builder.SetFillColor(fillColor);

  m_remaining--;
}

bool TxtShapeLoader::HasMore()
{
  return m_remaining > 0 && !m_file.eof();
}

void TxtShapeLoader::EndOpen()
{
  m_remaining--;

  if (m_remaining == 0)
    m_file.close();
}

std::shared_ptr<IDrawableShape> TxtShapeLoader::LoadShape()
{
  builder.Reset();

  ReadType();
  ReadPosition();
  ReadExtra();

  return builder.GetResult();
}
