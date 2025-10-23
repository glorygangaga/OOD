#pragma once

#include <iostream>
#include <fstream>

#include "include/CCanvas.hpp"
#include "include/shapes/CircleAdapterShape.hpp"
#include "include/shapes/TriangleAdapterShape.hpp"
#include "include/shapes/RectangleAdapterShape.hpp"

class Application
{
public:
  Application(const std::string &inputFileName, const std::string &outputFileName)
      : m_input(inputFileName), m_output(outputFileName), m_canvas(window::SIZE, window::SIZE, window::NAME) {};

  bool Start();

private:
  std::fstream m_input;
  std::ofstream m_output;
  CCanvas m_canvas;

  bool ProcessInput();
  std::shared_ptr<IDrawableShape> GetNewShape(const SHAPES_TYPE &shapeType);

  bool PushNewShape(std::shared_ptr<IDrawableShape> shape);

  std::shared_ptr<RectangleAdapterShape> CreateRectangle();
  std::shared_ptr<CircleAdapterShape> CreateCircle();
  std::shared_ptr<TriangleAdapterShape> CreateTriangle();
};
