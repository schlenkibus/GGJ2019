#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

class ResourceManager
{
 public:
  const char *prefix = "../resources/";
  const char *imgPrefix = "images/";
  const char *fonPrefix = "fonts/";
  const char *audioDir = "audio/";
  typedef std::string tPath;
  static ResourceManager &get();
  sf::Texture &getTexture(tPath path);
  sf::Font &getFont();
  sf::Music &getMusic();
  sf::SoundBuffer &getSoundBuffer(tPath path);

 protected:
  ResourceManager();
  std::unordered_map<tPath, sf::Texture> m_texture;
  std::unordered_map<tPath, sf::SoundBuffer> m_soundBuffer;
  sf::Music m_music;
  sf::Music m_backgroundNoise;
  sf::Font m_font;
};
