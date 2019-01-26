#pragma once

#include "DataManager.h"
#include "AnimalData.h"
#include "TenantCharacteristics.h"
#include <string>

class TenantData
{
 public:
  TenantData() = default;
  std::string toString() const;
  const std::string& getOutcome() const;
  sf::Texture& getTexture();
  Recommendation getRecommendationRating() { return recommendationRating; };
  Salary getSalaryRating() { return salaryRating; };

 protected:
  std::string name;
  std::string profession;
  int age{};
  int factor{};
  Recommendation recommendationRating;
  std::string recommendation;
  std::string outcome;
  int salary{};
  Salary salaryRating;
  AnimalData animaldata;
  bool happy = true;

  friend class TenantFactory;
};
