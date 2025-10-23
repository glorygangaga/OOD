#pragma once

#include <string>
#include <unordered_map>

namespace window
{
  const unsigned int SIZE = 500;
  const std::string NAME = "Window";
}

namespace inputs
{
  const std::string INPUT_FILENAME = "input.txt";
  const std::string OUTPUT_FILENAME = "output.txt";

  const std::string RECT = "RECTANGLE:";
  const std::string CIRCLE = "CIRCLE:";
  const std::string TRIANGLE = "TRIANGLE:";

  inline const char *RECT_SCAN = " P1=%d,%d; P2=%d,%d";
  inline const char *CIRCLE_SCAN = " C=%d,%d; R=%d";
  inline const char *TRIANGLE_SCAN = " P1=%d,%d; P2=%d,%d; P3=%d,%d";
}

namespace mathConstants
{
  const uint8_t CIRCLE_VALUE = 2;
}

namespace output
{
  const std::string PERIMETER = "P=";
  const std::string AREA = "S=";
  const std::string SEPARATOR = "; ";
}

enum class SHAPES_TYPE
{
  CIRCLE_T = 0,
  RECTANGLE_T,
  TRIANGLE_T
};

const std::unordered_map<std::string, SHAPES_TYPE> SHAPES_MAP = {
    {inputs::RECT, SHAPES_TYPE::RECTANGLE_T},
    {inputs::CIRCLE, SHAPES_TYPE::CIRCLE_T},
    {inputs::TRIANGLE, SHAPES_TYPE::TRIANGLE_T}};