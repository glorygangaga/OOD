#pragma once

#include <string>
#include <unordered_map>

namespace window
{
  const unsigned int SIZE = 700;
  const std::string NAME = "Window";

  const float frame_thickness = 2.f;
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

enum class SHAPE_COLORS
{
  RED,
  BLUE,
  BLACK,
  WHITE,
  YELLOW,
  TRANSPARENT
};

const int SHAPE_COLORS_SIZE = 6;

const std::unordered_map<SHAPE_COLORS, sf::Color> COLORS_MAP = {
    {SHAPE_COLORS::RED, sf::Color::Red},
    {SHAPE_COLORS::BLUE, sf::Color::Blue},
    {SHAPE_COLORS::BLACK, sf::Color::Black},
    {SHAPE_COLORS::WHITE, sf::Color::White},
    {SHAPE_COLORS::YELLOW, sf::Color::Yellow},
    {SHAPE_COLORS::TRANSPARENT, sf::Color::Transparent},
};

enum class SHAPE_COLOR_CHANGE
{
  THICKNESS,
  FILL,
};

enum class MODE
{
  DND,
  SHAPE_CHANGE,
};

const int MODE_SIZE = 2;