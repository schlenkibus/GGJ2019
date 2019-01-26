#include <iostream>
#include "GameStateManager.h"

#include "../Data/TenantFactory.h"
#include "../Application.h"
#include "../tools/AudioOneShotEngine.h"
#include "../UI/GameStuff/TenantKickScreen.h"

GameStateManager& GameStateManager::get()
{
  static GameStateManager gameStateManager;
  return gameStateManager;
}

void GameStateManager::acceptTenant()
{
  AudioOneShotEngine::get().play("happyTenant.wav");

  if (m_acceptedTenants.size() >= maxAmountOfTenants)
  {
    auto it = std::next(m_acceptedTenants.begin());

    std::move(m_acceptedTenants.begin(), std::next(m_acceptedTenants.begin()), std::back_inserter(m_thrownOutTenants));

    m_acceptedTenants.erase(m_acceptedTenants.begin());
  }

  m_acceptedTenants.push_back(m_currentTenant);

  Application::get().getLevel().install(std::make_unique<TenantKickScreen>());

  //newTenantFee();
  //nextDay();
}

void GameStateManager::declineTenant()
{
  AudioOneShotEngine::get().play("sadTenant.wav");
  m_declinedTenants.push_back(m_currentTenant);
  nextDay();
}

void GameStateManager::kickTenant(TenantData* tenant)
{
}

std::array<TenantData*, 3> GameStateManager::getKickCandidates()
{
  static auto t1 = TenantFactory::getTenant();
  static auto t2 = TenantFactory::getTenant();
  static auto t3 = TenantFactory::getTenant();

  return
  {
          &t1, &t2, &t3
  };
}

void GameStateManager::nextDay()
{
  if (m_days != 0 && m_days % 7 == 0) {
    calculateWeek();
  }

  m_days++;
  generateNewTenant();
}

void GameStateManager::generateNewTenant()
{
  m_currentTenant = std::make_shared<TenantData>(TenantFactory::getTenant());
  if(m_tenantChangedCallback)
  {
    m_tenantChangedCallback(m_currentTenant);
  }
}

void GameStateManager::listenForTenantChanged(TenantChangedCallback function)
{
  m_tenantChangedCallback = std::move(function);
}

void GameStateManager::newTenantFee()
{
  changeCurrentMoney(static_cast<int>(-newTenantCost));
}

void GameStateManager::changeCurrentMoney(int amount)
{
  m_currentMoneyEarned += amount;
  if(amount > 0)
  {
    m_totalMoneyEarned += amount;
  }
}

std::shared_ptr<TenantData> GameStateManager::getTenant()
{
  return m_currentTenant;
}

void GameStateManager::calculateWeek()
{
  size_t totalIncome = 0;
  for (auto& tenant : m_acceptedTenants)
  {
    totalIncome += calculateTenantPayment(tenant);
  }

  int netIncome = static_cast<int>(totalIncome - monthlyExpenses);

  changeCurrentMoney(netIncome);
}

size_t GameStateManager::calculateTenantPayment(std::shared_ptr<TenantData> tentant)
{
  auto recommendationRating = tentant->getRecommendationRating();
  auto salaryRating = tentant->getSalaryRating();

  const auto recommendationPercentage = [recommendationRating] {
      switch(recommendationRating)
      {
        case Recommendation::High:
          return 0.5f;
        case Recommendation::Medium:
          return 0.3f;
        case Recommendation::Low:
          return 0.1f;
        default:
          std::cerr << "recommendationRating unknown" << '\n';
          return 0.f;
      }
  }();

  const auto salaryPercentage = [salaryRating] {
      switch(salaryRating)
      {
        case Salary::High:
          return 0.5f;
        case Salary::Medium:
          return 0.3f;
        case Salary::Low:
          return 0.1f;
        default:
          std::cerr << "salaryRating unknown" << '\n';
          return 0.f;
      }
  }();

  const auto likelihood = (recommendationPercentage + salaryPercentage) * 100;
  auto& dm = DataManager::get();
  auto randomNumber = dm.getRandomNumber(0, 100);

  if (likelihood > randomNumber)
  {
    return rentAmount;
  }
  else
  {
    return 0;
  }
}

void GameStateManager::start()
{
  listenForTenantChanged([](std::shared_ptr<TenantData> ptr) { Application::get().getLevel().pushTenant(*ptr); });
  nextDay();
}
