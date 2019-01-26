#include <iostream>
#include "Level.h"
#include "ResourceManager.h"
#include "UI/Button.h"
#include "Application.h"

Level::Level() {
    auto& rm = ResourceManager::get();
    auto& testTexture = rm.getTexture("test.png");

    m_objects.emplace_back(std::make_unique<Button>(sf::Vector2f(300, 500), [](){
        Application::get().getLevel().pushMessage("I'm just an annoying Message! I don't care if this annoys you! :)");
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
    if(m_message)
        m_message->update(delta);
}

void Level::onEvent(sf::Event &e) {
    for(auto& obj: m_objects) {
        obj->onEvent(e);
    }
    if(m_message)
        m_message->onEvent(e);
}

void Level::draw(sf::RenderWindow &w) {
    for(auto& obj: m_objects) {
        obj->draw(w);
    }
    if(m_message)
        m_message->draw(w);
}

void Level::pushMessage(const std::string &message) {
    m_message = std::make_unique<MessageWindow>(message, "Common Message");
}

void Level::closeMessage() {
    m_message.reset(nullptr);
}