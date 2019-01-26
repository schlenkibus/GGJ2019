#include "TenantFactory.h"
#include "TenantData.h"
#include "TenantCharacteristics.h"

TenantData TenantFactory::getTenant()
{
  TenantData tenant;
  auto& dm = DataManager::get();
  tenant.name = dm.getName();
  tenant.salary = dm.getRandomNumber(0, 3500);
  tenant.age = dm.getRandomNumber(18, 100);
  tenant.factor = dm.getRandomNumber(-1, 1);
  tenant.outcome = dm.getOutcome();
  tenant.profession = dm.getProfession();

  std::string recommendation;
  Recommendation recommendationRating;

  switch(tenant.factor)
  {
    case -1:
      recommendation = dm.getRecommendationBad();
      recommendationRating = Recommendation::Low;
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
  switch(dm.getRandomNumber(-1, 1))
  {
    case -1:
      salaryRating = Salary::Low;
      break;
    case 1:
      salaryRating = Salary::High;
      break;
    case 0:
    default:
      salaryRating = Salary::Medium;
      break;
  }

  tenant.salaryRating = salaryRating;

  return tenant;
}