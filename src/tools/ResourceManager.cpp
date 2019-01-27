#include "ResourceManager.h"
#include "../UI/GameStuff/TenantKickScreen.h"

#include <iostream>

ResourceManager &ResourceManager::get()
{
  static ResourceManager rm;
  return rm;
}

sf::Texture &ResourceManager::getTexture(tPath path)
{
  path = prefix + std::string(imgPrefix) + path;
  try
  {
    return m_texture.at(path);
  }
  catch(...)
  {
    auto &tex = m_texture[path];
    auto ret = tex.loadFromFile(path);
    if(!ret)
    {
      std::cerr << "could not load texture from: " << path << '\n';
      exit(60);
    }
    return tex;
  }
}

sf::Font &ResourceManager::getFont()
{
  return m_font;
}

ResourceManager::ResourceManager()
{
  if(!m_font.loadFromFile(std::string(prefix) + fonPrefix + "Anonymous.ttf"))
  {
    std::cerr << "could not load font" << '\n';
  }

  if(!m_backgroundNoise.openFromFile(std::string(prefix) + std::string(audioDir) + "/ambient/office.wav"))
  {
    std::cerr << "could not load background noise\n";
  }

  if(!m_music.openFromFile(std::string(prefix) + std::string(audioDir) + "music.wav"))
  {
    std::cerr << "could not load music from: music.wav" << '\n';
  }

  m_music.setLoop(true);
  m_music.setVolume(12);
}

sf::Music &ResourceManager::getMusic()
{
  return m_music;
}

sf::SoundBuffer &ResourceManager::getSoundBuffer(ResourceManager::tPath path)
{
  path = std::string(prefix) + std::string(audioDir) + path;
  try
  {
    return m_soundBuffer.at(path);
  }
  catch(...)
  {
    auto &soundBuffer = m_soundBuffer[path];
    auto ret = soundBuffer.loadFromFile(path);
    if(!ret)
    {
      std::cerr << "could not load sound from: " << path << '\n';
      exit(60);
    }
    return soundBuffer;
  }
}