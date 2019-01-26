#include <iostream>
#include "Level.h"
#include "ResourceManager.h"
#include "UI/Button.h"
#include "Application.h"

Level::Level() {
    auto& rm = ResourceManager::get();
    auto& testTexture = rm.getTexture("test.png");

    m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 500), [](){
        Application::get().getLevel().pushMessage("Hallo!");
    }, "Test"));
    m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 600), [](){
        Application::get().quit();
    }, "Quit"));
    m_objects.emplace_back(std::make_unique<DrawableObject>(testTexture, sf::Vector2f(300, 100)));
}

void Level::update(float delta) {
    for(auto& obj: m_objects) {
        obj->update(delta);
    }
}

void Level::onEvent(sf::Event &e) {
    for(auto& obj: m_objects) {
        obj->onEvent(e);
    }
}

void Level::draw(sf::RenderWindow &w) {
    for(auto& obj: m_objects) {
        obj->draw(w);
    }
}

void Level::pushMessage(const std::string &message) {
    std::cout << "MESSAGE: " << message << std::endl;
}
