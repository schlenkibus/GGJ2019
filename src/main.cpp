#include "Application.h"
#include <iostream>

int main()
{
  auto &app = Application::get();
  app.run();
  return 0;
}