#include "include/tools/save/ShapeLoader.hpp"

std::vector<std::shared_ptr<IDrawableShape>> ShapeLoader::Load(const std::string &filename)
{
  std::vector<std::shared_ptr<IDrawableShape>> list;

  BeginOpen(filename);

  while (HasMore())
  {
    builder.Reset();

    ReadType();
    ReadPosition();
    ReadExtra();

    list.push_back(builder.GetResult());
  }

  EndOpen();

  if (!builder.GetUndrawChildren().empty())
    for (auto &s : builder.GetUndrawChildren())
      list.insert(list.begin(), s);

  return list;
}