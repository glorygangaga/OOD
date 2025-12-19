#pragma once

#include <fstream>
#include "include/tools/save/ShapeLoader.hpp"

class BinaryShapeLoader : public ShapeLoader
{
public:
  using ShapeLoader::ShapeLoader;

private:
  std::ifstream m_file;
  uint32_t m_remaining = 0;
  SHAPES_TYPE m_type;

  std::string m_filename;

  std::shared_ptr<IDrawableShape> LoadShape();

protected:
  void BeginOpen(const std::string &filename) override;
  void ReadType() override;
  void ReadPosition() override;
  void ReadExtra() override;
  bool HasMore() override;
  void EndOpen() override;
};
