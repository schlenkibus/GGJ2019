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

void CashView::setCash(int newValue)
{
  auto width = getGlobalBounds().width;
  setString("Cash: " + std::to_string(newValue) + "$");
  auto newWidth = getGlobalBounds().width;
  move(width - newWidth, 0);
}