#include "DayCounter.h"
#include "../../tools/ResourceManager.h"
#include "../../Game/GameStateManager.h"

DayCounter::DayCounter()
{
  setCharacterSize(30);
  setFillColor(sf::Color::White);
  setOutlineThickness(1.2);
  setOutlineColor(sf::Color::Black);
  setFont(ResourceManager::get().getFont());
  setPosition(1200 - getGlobalBounds().width, getGlobalBounds().height);
  GameStateManager::get().listenForDayChange([&](int day) {
    setString(std::string("Day ") + std::to_string(day));
    setPosition(1200 - getGlobalBounds().width, getGlobalBounds().height);
  });
}
