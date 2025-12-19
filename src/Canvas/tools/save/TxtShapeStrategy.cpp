#include "include/tools/save/TxtShapeStrategy.hpp"

void TxtShapeStrategy::Save(const std::vector<std::shared_ptr<IDrawableShape>> &shapes, const std::string &filename)
{
  std::ofstream out(filename);
  if (out.good() && !shapes.empty())
  {
    uint32_t count = static_cast<uint32_t>(shapes.size());
    out << count << '\n';

    for (auto &s : shapes)
      if (!s->InGroup())
        s->SerializeToText(out);
  }
}