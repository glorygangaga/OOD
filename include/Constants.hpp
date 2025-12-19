#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <map>

namespace window
{
  const unsigned int SIZE = 1000;
  const std::string NAME = "Window";

  const float frame_thickness = 2.f;
  const unsigned int FPS = 60;
}

namespace inputs
{
  const std::string INPUT_FILENAME = "input.txt";
  const std::string OUTPUT_FILENAME = "output.txt";

  const std::string BIN_FILENAME = "shapes.bin";
  const std::string TEXT_FILENAME = "shapes.txt";
  const std::string FONT_FILENAME = "arialmt.ttf";

  const std::string RECT = "RECTANGLE:";
  const std::string CIRCLE = "CIRCLE:";
  const std::string TRIANGLE = "TRIANGLE:";
  const std::string COMPOSITE = "COMPOSITE:";

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
  TRIANGLE_T,
  COMPOSITE_T,
  NONE
};

const std::unordered_map<std::string, SHAPES_TYPE> SHAPES_MAP = {
    {inputs::RECT, SHAPES_TYPE::RECTANGLE_T},
    {inputs::CIRCLE, SHAPES_TYPE::CIRCLE_T},
    {inputs::TRIANGLE, SHAPES_TYPE::TRIANGLE_T},
    {inputs::COMPOSITE, SHAPES_TYPE::COMPOSITE_T},
};

enum class Action
{
  SwitchMode,
  Thick1,
  Thick3,
  Thick5,
  ColorRed,
  ColorBlue,
  ColorWhite,
  ColorBlack,
  FillColorRed,
  FillColorBlue,
  FillColorWhite,
  FillColorBlack,
  AddRectangle,
  AddTriangle,
  AddCircle,
  LoadLastShapesBin,
  LoadLastShapesTxt
};

const std::vector<std::pair<sf::String, Action>> BUTTONS = {
    {"Switch mode", Action::SwitchMode},
    {"Thickness 1", Action::Thick1},
    {"Thickness 3", Action::Thick3},
    {"Thickness 5", Action::Thick5},
    {"Color red", Action::ColorRed},
    {"Color blue", Action::ColorBlue},
    {"Color white", Action::ColorWhite},
    {"Color black", Action::ColorBlack},
    {"Thick red", Action::FillColorRed},
    {"Thick blue", Action::FillColorBlue},
    {"Thick white", Action::FillColorWhite},
    {"Thick black", Action::FillColorBlack},
    {"Triangle", Action::AddTriangle},
    {"Rectangle", Action::AddRectangle},
    {"Circle", Action::AddCircle},
    {"Load bin", Action::LoadLastShapesBin},
    {"Load txt", Action::LoadLastShapesTxt},
};