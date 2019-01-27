#pragma once

#include "DataManager.h"
#include "TenantCharacteristics.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class TenantData
{
 public:
  enum AnimalType
  {
    Cat,
    Dog,
    Bunny,
    Snake,
    Jellyfish,
    Bear
  };

  TenantData() = default;
  TenantData(const TenantData& other);
  std::string toString() const;
  std::string getOutcome() const;
  std::string getStats() const;
  sf::Texture& getTexture();
  std::string getSoundName();
  std::string getAngryName();
  void setReason(std::string reason);
  const std::string toString(AnimalType) const;
  Recommendation getRecommendationRating()
  {
    return recommendationRating;
  };
  Salary getSalaryRating()
  {
    return salaryRating;
  };
  void setHappy(bool h)
  {
    happy = h;
  }

 protected:
  std::string name;
  std::string profession;
  std::string reason;
  int age{};
  int factor{};
  Recommendation recommendationRating{};
  AnimalType type{};
  std::string recommendation;
  std::string outcome;
  int salary{};
  Salary salaryRating{};
  bool happy = true;

  friend class TenantFactory;
};
