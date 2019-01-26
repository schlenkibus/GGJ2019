#include "AnimalData.h"


AnimalData::AnimalData(AnimalData::AnimalType type) {
    prefix = "faces/";
    switch(type) {
        case AnimalType::Bunny:
            prefix += "bunny-";
            break;
        case Cat:
            prefix += "cat-";
            break;
        case Dog:
            prefix += "dog-";
            break;
        case Snake:
            prefix += "snake-";
            break;
    }
}

sf::Texture& AnimalData::getTexture(bool isHappy) {
    auto s = isHappy ? "happy" : "sad";
    return ResourceManager::get().getTexture(prefix + s + ".png");
}

sf::Texture& AnimalData::getSound(bool isHappy) {
    auto s = isHappy ? "happy" : "sad";
    return ResourceManager::get().getTexture(prefix + s + ".wav");
}