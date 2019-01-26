#include "AnimalData.h"

AnimalData::AnimalData(AnimalData::AnimalType type)
{
  prefix = "faces/";
  switch(type)
  {
    case AnimalType::Bunny:
      prefix += "bunny_";
      break;
    case Cat:
      prefix += "cat_";
      break;
    case Dog:
      prefix += "dog_";
      break;
    case Snake:
      prefix += "snake_";
      break;
  }
}

sf::Texture& AnimalData::getTexture(bool isHappy)
{
  auto s = isHappy ? "happy" : "sad";
  return ResourceManager::get().getTexture(prefix + s + ".jpg");
}

sf::Texture& AnimalData::getSound(bool isHappy)
{
  auto s = isHappy ? "happy" : "sad";
  return ResourceManager::get().getTexture(prefix + s + ".wav");
}