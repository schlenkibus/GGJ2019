#include <utility>
#include <sstream>
#include "TenantData.h"
#include "../tools/ResourceManager.h"

TenantData::TenantData(const TenantData& other)
{
  name = other.name;
  reason = other.reason;
  age = other.age;
  type = other.type;
  profession = other.profession;
  salary = other.salary;
  salaryRating = other.salaryRating;
  recommendationRating = other.recommendationRating;
  recommendation = other.recommendation;
  happy = other.happy;
  outcome = other.outcome;
  factor = other.factor;
}

std::string TenantData::toString() const
{
  std::stringstream ss;
  ss << "Name: " << name << "\n";
  ss << "Age: " << age << "\n";
  ss << "Kind: " << toString(type) << '\n';
  ss << "Profession: " << profession << "\n";
  ss << "Salary: " << salary << "\n";
  ss << "Recommendation:\n" << recommendation << "\n";
  return ss.str();
}

std::string TenantData::getOutcome() const
{
  std::string ret{};
  ret += "Because you";
  ret += reason;
  ret += name;
  ret += " the ";
  ret += toString(type);
  ret += ":\n\n";
  ret += name;
  ret += " ";
  ret += static_cast<char>(std::tolower(static_cast<int>(outcome[0])));
  ret += outcome.substr(1);
  return ret;
}

const std::string TenantData::toString(TenantData::AnimalType type) const
{
  switch(type)
  {
    case Dog:
      return "Dog";
    case Cat:
      return "Cat";
    case Bunny:
      return "Bunny";
    case Snake:
      return "Snake";
  }
}

sf::Texture& TenantData::getTexture()
{
  std::string prefix = [&](std::string s) {
    s[0] = std::tolower(s[0]);
    s += "_";
    return s;
  }(toString(type));
  auto s = happy ? "happy" : "sad";
  return ResourceManager::get().getTexture("faces/" + prefix + s + ".jpg");
}

std::string TenantData::getStats() const
{
  std::string ret;
  switch(recommendationRating)
  {
    case Recommendation::High:
      ret += ":)";
      break;
    case Recommendation::Medium:
      ret += ":|";
      break;
    case Recommendation::Low:
      ret += ":(";
      break;
  }
  ret += ' ';
  switch(salaryRating)
  {
    case Salary::High:
      ret += "$$$";
      break;
    case Salary::Medium:
      ret += "$$";
      break;
    case Salary::Low:
      ret += "$";
      break;
  }
  return ret;
}

void TenantData::setReason(std::string reason)
{
  this->reason = std::move(reason);
}

std::string TenantData::getSoundName()
{
  auto ret = std::string(happy ? "happy" : "sad") + "Tenant.wav";
  return ret;
  std::string prefix = [&](std::string s) {
    s[0] = std::tolower(s[0]);
    s += "_";
    return s;
  }(toString(type));
  auto s = happy ? "happy" : "sad";
  return std::string(prefix + s + ".wav");
}
