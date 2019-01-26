#include "Application.h"
#include "Game/Level.h"
#include <SFML/Window/Event.hpp>

Application &Application::get()
{
  static Application app;
  return app;
}

Application::Application()
    : window{ sf::VideoMode(1366, 768), "GGJ19", sf::Style::Fullscreen }
    , level{}
{
}

void Application::run()
{
  sf::Event event{};

  sf::Clock clock;

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

void Application::quit()
{
  window.close();
  exit(6);
}

const sf::Vector2f Application::getMidPoint() const
{
  return sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
}
