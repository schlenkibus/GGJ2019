#include "AudioOneShotEngine.h"
#include "ResourceManager.h"

#include <string>

AudioOneShotEngine& AudioOneShotEngine::get()
{
  static AudioOneShotEngine rm;
  return rm;
}

void AudioOneShotEngine::play(std::string path)
{
  auto& sound = getNextSound();

  auto& soundBuffer = ResourceManager::get().getSoundBuffer(path);

  sound.setBuffer(soundBuffer);
  sound.play();
}

sf::Sound& AudioOneShotEngine::getNextSound()
{
  if(index >= sounds.size())
  {
    index = 0;
  }

  return sounds[index++];
}
