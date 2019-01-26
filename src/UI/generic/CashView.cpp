#include "CashView.h"
#include "../../tools/ResourceManager.h"


CashView::CashView() {
    setCharacterSize(40);
    setFillColor(sf::Color::White);
    setOutlineThickness(2);
    setOutlineColor(sf::Color::Black);
    setFont(ResourceManager::get().getFont());
}

CashView::CashView(int initalValue, sf::Vector2f position) {
    setPosition(position);
    setCash(initalValue);
    setCharacterSize(40);
    setFillColor(sf::Color::White);
    setOutlineThickness(2);
    setOutlineColor(sf::Color::Black);
    setFont(ResourceManager::get().getFont());
}

void CashView::setCash(int newValue) { setString("Cash: " + std::to_string(newValue) + "$"); }