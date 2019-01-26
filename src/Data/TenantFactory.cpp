#include "TenantFactory.h"
#include "TenantData.h"

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

  std::string reccomendation;

  switch(tenant.factor)
  {
    case -1:
      reccomendation = dm.getRecommendationBad();
      break;
    case 1:
      reccomendation = dm.getRecommendationGood();
      break;
    case 0:
    default:
      reccomendation = dm.getRecommendationNeural();
      break;
  }

  tenant.reccomendation = reccomendation;
  return tenant;
}