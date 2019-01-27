#pragma once

#include "DataManager.h"
#include "TenantCharacteristics.h"
#include <string>
#include <memory>
#include <SFML/Graphics/Texture.hpp>

class TenantData : public std::enable_shared_from_this<TenantData>
{
 public:
  enum AnimalType
  {
    Cat,
    Dog,
    Bunny,
    Snake
  };

  TenantData() = default;
  std::shared_ptr<TenantData> shared()
  {
    return shared_from_this();
  }
  std::string toString() const;
  std::string getOutcome() const;
  std::string getStats() const;
  sf::Texture& getTexture();
  std::string getSoundName();
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
