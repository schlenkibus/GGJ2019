#include "TenantFactory.h"
#include "TenantData.h"
#include "TenantCharacteristics.h"

TenantData TenantFactory::getTenant()
{
  TenantData tenant;
  auto& dm = DataManager::get();
  tenant.name = dm.getName();
  tenant.salary = dm.getRandomNumber(500, 3500);
  tenant.age = dm.getRandomNumber(18, 85);
  tenant.factor = dm.getRandomNumber(-1, 1);
  tenant.outcome = dm.getOutcome();
  tenant.profession = dm.getProfession();
  tenant.reason = " NONE ";
  tenant.type = []() {
    auto rand = std::rand() % 5;
    switch(rand)
    {
      case 0:
        return TenantData::Cat;
      case 1:
        return TenantData::Snake;
      case 2:
        return TenantData::Dog;
      case 3:
        return TenantData::Bunny;
      case 4:
      default:
        return TenantData::Jellyfish;
    }
  }();

  std::string recommendation;
  Recommendation recommendationRating;

  switch(tenant.factor)
  {
    case -1:
      recommendation = dm.getRecommendationBad();
      recommendationRating = Recommendation::Low;
      tenant.outcome = "was bad news, Good pass!";
      break;
    case 1:
      recommendation = dm.getRecommendationGood();
      recommendationRating = Recommendation::High;
      break;
    case 0:
    default:
      recommendation = dm.getRecommendationNeural();
      recommendationRating = Recommendation::Medium;
      break;
  }

  tenant.recommendation = recommendation;
  tenant.recommendationRating = recommendationRating;

  Salary salaryRating;
  if(tenant.salary > 2500)
  {
    salaryRating = Salary::High;
  }
  else if(tenant.salary > 1500)
  {
    salaryRating = Salary::Medium;
  }
  else
  {
    salaryRating = Salary::Low;
  }

  tenant.salaryRating = salaryRating;

  return tenant;
}