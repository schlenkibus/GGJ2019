#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <array>

class AudioOneShotEngine
{
 public:
  static AudioOneShotEngine& get();
  void play(std::string path);

 private:
  sf::Sound& getNextSound();

  std::array<sf::Sound, 5> sounds{};
  size_t index = 0;
};
