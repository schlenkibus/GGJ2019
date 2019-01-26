#pragma once

#include "../tools/ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>

#include <string>

class AnimalData
{
 public:
  enum AnimalType
  {
    Cat,
    Dog,
    Bunny,
    Snake
  };

  explicit AnimalData(AnimalType type = Bunny);
  sf::Texture& getTexture(bool isHappy);
  std::string getSoundName(bool isHappy);

 protected:
  ResourceManager::tPath prefix{};
};
