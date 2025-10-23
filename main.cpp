#include "include/app.hpp"

int main()
{
  Application app(inputs::INPUT_FILENAME, inputs::OUTPUT_FILENAME);
  app.Start();
  return 0;
}