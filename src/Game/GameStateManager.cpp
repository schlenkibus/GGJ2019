#include <iostream>
#include "GameStateManager.h"

#include "../Data/TenantFactory.h"
#include "../Application.h"
#include "../tools/AudioOneShotEngine.h"
#include "../UI/GameStuff/TenantKickScreen.h"
#include "../UI/GameStuff/PlayerStatsScreen.h"
#include "../UI/GameStuff/DenyTenantScreen.h"
#include "../UI/GameStuff/GameOverScreen.h"
#include <random>
#include <assert.h>
#include <sstream>

GameStateManager::GameStateManager()
{
  for(auto i = 0; i < m_acceptedTenants.max_size(); i++)
  {
    m_acceptedTenants[i] = std::make_shared<TenantData>(TenantFactory::getTenant());
  }

  for(auto& e : m_acceptedTenants)
  {
    assert(e.get() != nullptr);
  }
}

void GameStateManager::init()
{
  m_days = 0;
  setMoney(5000);
  m_tenantsKickedOut = 0;
  m_currentKarmaEarned = 0;
  m_totalMoneyEarned = 0;
  m_totalKarmaEarned = 0;
}

GameStateManager& GameStateManager::get()
{
  static GameStateManager gameStateManager;
  return gameStateManager;
}

void GameStateManager::acceptTenant()
{
  m_currentTenant->setHappy(true);
  AudioOneShotEngine::get().play(m_currentTenant->getSoundName());
}

void GameStateManager::declineTenant()
{
  m_currentTenant->setHappy(false);
  m_currentTenant->setReason(" declined ");
  AudioOneShotEngine::get().play(m_currentTenant->getSoundName());
  m_declinedTenants.push_back(m_currentTenant);
}

void GameStateManager::kickTenant(TenantData* tenant)
{
  auto backup = std::make_shared<TenantData>(*tenant);

  for(auto& e : m_acceptedTenants)
  {
    if(e.get() == tenant)
    {
      e = std::make_shared<TenantData>(*m_currentTenant.get());
      break;
    }
  }

  backup->setReason(" kicked out ");
  backup->setHappy(false);
  m_currentTenant = std::make_shared<TenantData>(*backup.get());
  newTenantFee();
}

std::string GameStateManager::getWeeklyReport()
{
  std::stringstream ss;
  ss << "Net Income: " << m_netIncome - static_cast<int>(m_tenantsKickedOut * newTenantCost) << '\n';
  ss << "Tenants Replaced: " << m_tenantsKickedOut << '\n';
  ss << "Total Money: " << m_currentMoneyEarned << '\n';
  m_netIncome = 0;
  m_tenantsKickedOut = 0;
  return ss.str();
}

std::string GameStateManager::getGameOverMessage()
{
  std::stringstream ss;
  ss << "Lifes Destroyed: " << m_lifesDestroyed << '\n';
  ss << "Are you happy now?";
  return ss.str();
}

std::array<TenantData*, 3> GameStateManager::getKickCandidates()
{
  std::vector<std::shared_ptr<TenantData>> out;
  std::sample(m_acceptedTenants.begin(), m_acceptedTenants.end(), std::back_inserter(out), 3,
              std::mt19937{ std::random_device{}() });
  return { out[0].get(), out[1].get(), out[2].get() };
}

size_t GameStateManager::nextDay()
{
  generateNewTenant();
  m_dayChangedCallback(static_cast<int>(m_days + 1));
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

void GameStateManager::listenForMoneyChange(MoneyChangedCallback function)
{
  m_moneyChanged = std::move(function);
}

void GameStateManager::listenForTenantChanged(TenantChangedCallback function)
{
  m_tenantChangedCallback = std::move(function);
}

void GameStateManager::newTenantFee()
{
  changeCurrentMoney(static_cast<int>(-newTenantCost));
}

void GameStateManager::setMoney(int money)
{
  m_currentMoneyEarned = money;
  m_moneyChanged(m_currentMoneyEarned);
}

void GameStateManager::changeCurrentMoney(int amount)
{
  m_currentMoneyEarned += amount;
  if(amount > 0)
  {
    m_totalMoneyEarned += amount;
  }

  m_moneyChanged(m_currentMoneyEarned);
}

std::shared_ptr<TenantData> GameStateManager::getTenant()
{
  return m_currentTenant;
}

void GameStateManager::calculateWeek()
{
  size_t totalIncome = 0;
  for(auto& tenant : m_acceptedTenants)
  {
    totalIncome += calculateTenantPayment(tenant);
  }

  m_netIncome = static_cast<int>(totalIncome - monthlyExpenses);

  changeCurrentMoney(m_netIncome);
}

size_t GameStateManager::calculateTenantPayment(std::shared_ptr<TenantData> tentant)
{
  auto recommendationRating = tentant->getRecommendationRating();
  auto salaryRating = tentant->getSalaryRating();

  const auto recommendationPercentage = [recommendationRating] {
    switch(recommendationRating)
    {
      case Recommendation::High:
        return 0.42f;
      case Recommendation::Medium:
        return 0.2f;
      case Recommendation::Low:
        return 0.05f;
      default:
        std::cerr << "recommendationRating unknown" << '\n';
        return 0.f;
    }
  }();

  const auto salaryPercentage = [salaryRating] {
    switch(salaryRating)
    {
      case Salary::High:
        return 0.4f;
      case Salary::Medium:
        return 0.2f;
      case Salary::Low:
        return 0.05f;
      default:
        std::cerr << "salaryRating unknown" << '\n';
        return 0.f;
    }
  }();

  const auto likelihood = (recommendationPercentage + salaryPercentage) * 100;
  auto& dm = DataManager::get();
  auto randomNumber = dm.getRandomNumber(0, 100);

  if(likelihood > randomNumber)
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
  static ScreenState screenState{ ScreenState::Start };

  screenState = newScreenState;

  switch(screenState)
  {
    case ScreenState::Start:
    {

      break;
    }
    case ScreenState::NewTenant:
    {
      if((m_days != 0) && (m_days % 7 == 0) && (m_days != lastCalculatedDay))
      {
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
      m_tenantsKickedOut++;
      m_lifesDestroyed++;
      Application::get().getLevel().install(std::make_unique<TenantKickScreen>());
      break;
    }
    case ScreenState::KickTenantAfter:
    {
      Application::get().getLevel().install(std::make_unique<AfterKickTenantScreem>());
      break;
    }
    case ScreenState::DenyTenant:
    {
      m_lifesDestroyed++;
      m_currentTenant->setHappy(false);
      Application::get().getLevel().install(std::make_unique<DenyTenantScreen>());
      break;
    }
    case ScreenState::PlayerStats:
    {
      lastCalculatedDay = m_days;
      calculateWeek();
      Application::get().getLevel().install(std::make_unique<PlayerStatsScreen>());
      break;
    }
    case ScreenState::GameOver:
    {
      Application::get().getLevel().install(std::make_unique<GameOverScreen>());
      break;
    }
  }
}

std::shared_ptr<TenantData> GameStateManager::getKickedTenant()
{
  return m_currentTenant;
}

void GameStateManager::listenForDayChange(GameStateManager::DayChangedCallback cb)
{
  m_dayChangedCallback = std::move(cb);
}
