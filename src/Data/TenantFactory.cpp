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
  Recommendation recommendationValue;

  switch(tenant.factor)
  {
    case -1:
      recommendation = dm.getRecommendationBad();
      recommendationValue = Recommendation::Low;
      break;
    case 1:
      recommendation = dm.getRecommendationGood();
      recommendationValue = Recommendation::High;
      break;
    case 0:
    default:
      recommendation = dm.getRecommendationNeural();
      recommendationValue = Recommendation::Medium;
      break;
  }

  tenant.recommendation = recommendation;
  tenant.recommendationValue = recommendationValue;

  Salary salaryValue;
  switch(dm.getRandomNumber(-1, 1))
  {
    case -1:
      salaryValue = Salary::Low;
      break;
    case 1:
      salaryValue = Salary::High;
      break;
    case 0:
    default:
      salaryValue = Salary::Medium;
      break;
  }

  tenant.salaryValue = salaryValue;

  return tenant;
}