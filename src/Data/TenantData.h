#pragma once

#include "DataManager.h"
#include "AnimalData.h"
#include "TenantCharacteristics.h"
#include <string>
#include <memory>

class TenantData : public std::enable_shared_from_this<TenantData>
{
 public:
  TenantData() = default;
  std::shared_ptr<TenantData> shared()
  {
    return shared_from_this();
  }
  std::string toString() const;
  const std::string& getOutcome() const;
  std::string getStats() const;
  sf::Texture& getTexture();
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
  Recommendation recommendationRating;
  std::string recommendation;
  std::string outcome;
  int salary{};
  Salary salaryRating;
  AnimalData animaldata;
  bool happy = true;

  friend class TenantFactory;
};
