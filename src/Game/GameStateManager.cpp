#include <iostream>
#include "GameStateManager.h"

#include "../Data/TenantFactory.h"
#include "../Application.h"
#include "../tools/AudioOneShotEngine.h"
#include "../UI/GameStuff/TenantKickScreen.h"
#include <assert.h>

GameStateManager::GameStateManager() {
  for(auto i = 0; i < m_acceptedTenants.max_size(); i++) {
    m_acceptedTenants[i] = std::make_shared<TenantData>(TenantFactory::getTenant());
  }

  for(auto& e: m_acceptedTenants) {
    assert(e.get() != nullptr);
  }
}

GameStateManager& GameStateManager::get()
{
  static GameStateManager gameStateManager;
  return gameStateManager;
}

void GameStateManager::acceptTenant()
{
  AudioOneShotEngine::get().play("happyTenant.wav");
}

void GameStateManager::declineTenant()
{
  AudioOneShotEngine::get().play("sadTenant.wav");
  m_declinedTenants.push_back(m_currentTenant);
  nextDay();
}

void GameStateManager::kickTenant(TenantData* tenant)
{
  for(auto& e: m_acceptedTenants) {
    if(e.get() == tenant) {
      e.reset(m_currentTenant.get());
      break;
    }
  }

  newTenantFee();
  setScreenState(ScreenState::NewTenant);
}

std::array<TenantData*, 3> GameStateManager::getKickCandidates()
{
  return
  {
          m_acceptedTenants[0].get(),
          m_acceptedTenants[1].get(),
          m_acceptedTenants[2].get()
  };
}

size_t GameStateManager::nextDay()
{
  generateNewTenant();
  return ++m_days;
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
  Application::get().getLevel().setGameScene();
  setScreenState(ScreenState::NewTenant);
}

void GameStateManager::setScreenState(ScreenState newScreenState)
{
  static ScreenState screenState{ScreenState::Start};

  screenState = newScreenState;

  switch (screenState)
  {
    case ScreenState::Start:
    {

      break;
    }
    case ScreenState::NewTenant:
    {
      if (m_days != 0 && m_days % 7 == 0) {
        setScreenState(ScreenState::PlayerStats);
      }
      else
      {
        nextDay();
        Application::get().getLevel().pushTenant(*m_currentTenant);
      }

      break;
    }
    case ScreenState::KickTenant:
    {
      Application::get().getLevel().install(std::make_unique<TenantKickScreen>());
      break;
    }
    case ScreenState::DenyTenant:
    {
//      Application::get().getLevel().install(std::make_unique<DenyTenantScreen>());
      break;
    }
    case ScreenState::PlayerStats:
    {
      calculateWeek();
//      Application::get().getLevel().install(std::make_unique<PlayerStatsScreen>());
      break;
    }
  }
}
