#include "CashView.h"
#include "../../tools/ResourceManager.h"
#include "../../Game/GameStateManager.h"

CashView::CashView()
{
  setCharacterSize(30);
  setFillColor(sf::Color::White);
  setOutlineThickness(1.2);
  setOutlineColor(sf::Color::Black);
  setFont(ResourceManager::get().getFont());
  GameStateManager::get().listenForMoneyChange([&](int money) { setCash(money); });
}

CashView::CashView(int initalValue, sf::Vector2f position)
{
  setPosition(position);
  setCash(initalValue);
  setCharacterSize(40);
  setFillColor(sf::Color::White);
  setOutlineThickness(2);
  setOutlineColor(sf::Color::Black);
  setFont(ResourceManager::get().getFont());
}

void CashView::setCash(int newValue)
{
  setString("Cash: " + std::to_string(newValue) + "$");
}