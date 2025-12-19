#include "include/tools/save/BinaryShapeStrategy.hpp"

void BinaryShapeStrategy::Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename)
{
  std::ofstream out(filename, std::ios::binary | std::ios::trunc);

  if (out.good() && !shapes.empty())
  {
    uint32_t count = static_cast<uint32_t>(shapes.size());
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));

    for (auto &s : shapes)
      if (!s->InGroup())
        s->SerializeToBinary(out);
  }
}