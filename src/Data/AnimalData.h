#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "../tools/ResourceManager.h"

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
  sf::Texture& getSound(bool isHappy);

 protected:
  ResourceManager::tPath prefix{};
};
