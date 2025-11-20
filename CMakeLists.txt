cmake_minimum_required(VERSION 3.10)

project(shapes)

set(CMAKE_CXX_STANDARD 17)

add_executable(shapes
    main.cpp
    src/app.cpp
    src/Canvas/CCanvas.cpp
    src/Shapes/CircleAdapterShape.cpp
    src/Shapes/TriangleAdapterShape.cpp
    src/Shapes/RectangleAdapterShape.cpp
    src/Shapes/SFML/SfmlCircle.cpp
    src/Shapes/SFML/SfmlTriangle.cpp
    src/Shapes/SFML/SfmlRectangle.cpp
    src/Shapes/CompositeShape.cpp
    src/Canvas/tools/states/AddShapeState.cpp
    src/Canvas/tools/states/ChangeColorShapeState.cpp
    src/Canvas/tools/states/ChangeThicknessShapeState.cpp
    src/Canvas/tools/states/DragState.cpp
    src/Canvas/tools/states/ChangeColorThickness.cpp
    src/Canvas/tools/commands/ChangeColorCommand.cpp
    src/Canvas/tools/commands/AddShapeCommand.cpp
    src/Canvas/tools/commands/ChangeThicknessCommand.cpp
    src/Canvas/tools/commands/DragCommand.cpp
    src/Canvas/tools/commands/ChangeColorCommandFill.cpp
    src/Canvas/ui/button/Button.cpp
    src/Canvas/ui/Panel.cpp
)


configure_file(input.txt ${CMAKE_CURRENT_BINARY_DIR}/input.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/include/ui/font/arialmt.ttf ${CMAKE_CURRENT_BINARY_DIR}/arialmt.ttf COPYONLY)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(shapes sfml-graphics sfml-window sfml-system)
target_include_directories(shapes PRIVATE ${CMAKE_SOURCE_DIR})