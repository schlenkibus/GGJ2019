#include "Level.h"
#include "ResourceManager.h"

Level::Level() {
    auto& rm = ResourceManager::get();
    auto& testTexture = rm.getTexture("test.png");
    DrawableObject obj{testTexture, sf::Vector2f(300, 200), [](sf::Event& e, DrawableObject& myObject) {

    }, [](float delta, DrawableObject& myObject) {

    }};
    m_objects.emplace_back(std::move(obj));
}

void Level::update(float delta) {
    for(auto& obj: m_objects) {
        obj.update(delta);
    }
}

void Level::onEvent(sf::Event &e) {
    for(auto& obj: m_objects) {
        obj.onEvent(e);
    }
}

void Level::draw(sf::RenderWindow &w) {
    for(auto& obj: m_objects) {
        obj.draw(w);
    }
}