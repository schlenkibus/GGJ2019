#pragma once

#include "DataManager.h"
#include "AnimalData.h"
#include <string>

class TenantData
{
 public:
  TenantData() = default;
  std::string toString() const;
  const std::string& getOutcome() const;
  sf::Texture& getTexture();

 protected:
  std::string name;
  std::string profession;
  int age{};
  int factor{};
  std::string reccomendation;
  std::string outcome;
  int salary{};
  AnimalData animaldata;
  bool happy = true;

  friend class TenantFactory;
};
