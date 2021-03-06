#include "Application.h"
#include "Game/Level.h"
#include "Data/DataManager.h"
#include "Data/TenantFactory.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Application &Application::get()
{
  static Application app;
  return app;
}

Application::Application()
    : window{ sf::VideoMode(1200, 650), "GGJ19", sf::Style::Fullscreen }
    , level{}
{
}

void Application::run()
{
  auto &d = DataManager::get();
  sf::Event event{};
  sf::Clock clock;
  level.start();

  while(window.isOpen())
  {
    while(window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          window.close();
          exit(0);
        default:
          level.onEvent(event);
          break;
      }
    }

    auto delta = clock.getElapsedTime().asMilliseconds();
    level.update(delta);
    clock.restart();

    window.clear();
    level.draw(window);
    window.display();
  }
}

sf::Vector2i Application::getMouse() const
{
  return sf::Mouse::getPosition(window);
}

Level &Application::getLevel()
{
  return level;
}

const sf::Vector2f Application::getMidPoint() const
{
  return sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);
}
