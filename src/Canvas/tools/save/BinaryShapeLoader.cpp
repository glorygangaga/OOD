#include "include/tools/save/BinaryShapeLoader.hpp"

void BinaryShapeLoader::BeginOpen(const std::string &filename)
{
  m_filename = filename;

  m_file.open(filename, std::ios::binary);
  m_file.read(reinterpret_cast<char *>(&m_remaining), sizeof(uint32_t));
}

void BinaryShapeLoader::ReadType()
{
  SHAPES_TYPE type;
  m_file.read(reinterpret_cast<char *>(&type), sizeof(SHAPES_TYPE));
  m_type = type;

  builder.SetType(type);
}

void BinaryShapeLoader::ReadPosition()
{

  if (m_type != SHAPES_TYPE::NONE && m_type != SHAPES_TYPE::COMPOSITE_T)
  {
    float x, y;
    m_file.read(reinterpret_cast<char *>(&x), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y), sizeof(float));
    builder.SetPosition({x, y});
  }
}

void BinaryShapeLoader::ReadExtra()
{
  switch (m_type)
  {
  case SHAPES_TYPE::CIRCLE_T:
  {
    float x, y, radius;
    m_file.read(reinterpret_cast<char *>(&x), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&radius), sizeof(float));

    builder.SetCircleData({x, y}, radius);
    break;
  }
  case SHAPES_TYPE::RECTANGLE_T:
  {
    float x1, y1, x2, y2;

    m_file.read(reinterpret_cast<char *>(&x1), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y1), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&x2), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y2), sizeof(float));

    builder.SetRectangleData({x1, y1}, {x2, y2});
    break;
  }
  case SHAPES_TYPE::TRIANGLE_T:
  {
    float x1, y1, x2, y2, x3, y3;

    m_file.read(reinterpret_cast<char *>(&x1), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y1), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&x2), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y2), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&x3), sizeof(float));
    m_file.read(reinterpret_cast<char *>(&y3), sizeof(float));

    builder.SetTriangleData({x1, y1}, {x2, y2}, {x3, y3});
    break;
  }
  case SHAPES_TYPE::COMPOSITE_T:
  {
    uint32_t size;
    m_file.read(reinterpret_cast<char *>(&size), sizeof(uint32_t));

    std::vector<std::shared_ptr<IDrawableShape>> shapes;

    for (uint32_t i = 0; i < size; i++)
    {
      auto shape = LoadShape();
      shapes.push_back(shape);
    }

    builder.SetCompositeData(shapes);
    builder.SetType(SHAPES_TYPE::COMPOSITE_T);

    return;
  }
  default:
    return;
  }

  uint32_t outlineColor;
  m_file.read(reinterpret_cast<char *>(&outlineColor), sizeof(uint32_t));
  builder.SetOutlneColor(outlineColor);

  float thickness;
  m_file.read(reinterpret_cast<char *>(&thickness), sizeof(float));
  builder.SetOutlineThickness(thickness);

  uint32_t fillColor;
  m_file.read(reinterpret_cast<char *>(&fillColor), sizeof(uint32_t));
  builder.SetFillColor(fillColor);

  m_remaining--;
}

bool BinaryShapeLoader::HasMore()
{
  return m_remaining > 0 && !m_file.eof();
}

void BinaryShapeLoader::EndOpen()
{
  m_remaining--;

  if (m_remaining == 0)
    m_file.close();
}

std::shared_ptr<IDrawableShape> BinaryShapeLoader::LoadShape()
{
  builder.Reset();

  ReadType();
  ReadPosition();
  ReadExtra();

  return builder.GetResult();
}
