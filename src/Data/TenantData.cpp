#include <sstream>
#include "TenantData.h"

std::string TenantData::toString() const
{
  std::stringstream ss;
  ss << "Name:" << name << '\n';
  ss << "Age:" << age << '\n';
  ss << "Profession:" << profession << '\n';
  ss << "Salary:" << salary << '\n';
  ss << "Recommendation:\n" << recommendation << '\n';
  return ss.str();
}

const std::string& TenantData::getOutcome() const
{
  return outcome;
}

sf::Texture &TenantData::getTexture() {
  return animaldata.getTexture(happy);
}
