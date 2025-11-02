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
  static Application &Instance()
  {
    static Application instance;
    return instance;
  }

  bool Start();

  Application(const Application &) = delete;
  Application(Application &&) = delete;
  Application &operator=(const Application &) = delete;
  Application &operator=(Application &&) = delete;

private:
  Application()
      : m_input(inputs::INPUT_FILENAME),
        m_output(inputs::OUTPUT_FILENAME),
        m_canvas(window::SIZE, window::SIZE, window::NAME) {};

  ~Application() = default;

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
