#pragma once
#include "Game/Level.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Application
{
 public:
  static Application &get();
  void run();
  sf::Vector2i getMouse() const;
  Level &getLevel();
  const sf::Vector2f getMidPoint() const;

 protected:
  Application();
  sf::RenderWindow window;
  Level level;
};
