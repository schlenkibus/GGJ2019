#include <iosfwd>
#include <fstream>
#include <iostream>
#include <sstream>
#include "DataManager.h"
#include <algorithm>
#include <random>
#include <utility>
#include <functional>

DataManager::DataManager()
{
  auto names = std::ifstream("../resources/data/names_formatted");
  std::string line;
  while(std::getline(names, line))
  {
    std::string o{};
    bool first = true;
    for(auto& c : line)
    {
      if(!first)
        o += static_cast<char>(std::tolower(c));
      else
        o += c;
      first = false;
    }
    if(!o.empty())
      m_names.emplace_back(o);
  }
  names.close();

  auto splitStringOnAnyDelimiter = [](const std::string& s, char delimiter) -> std::vector<std::string> {
    std::vector<std::string> strings;
    std::string token;
    std::istringstream tokenStream(s);
    while(std::getline(tokenStream, token, delimiter))
    {
      std::string o{};
      for(auto& c : token)
      {
        if(std::isprint(c))
          o += c;
      }
      if(!o.empty())
        strings.push_back(o);
    }

    while(strings.size() < 5)
      strings.emplace_back("");
    return strings;
  };

  auto dataFile = std::ifstream("../resources/data/characters.tsv");
  bool first = true;
  while(std::getline(dataFile, line))
  {
    if(first)
    {
      first = false;
      continue;
    }

    auto strings = splitStringOnAnyDelimiter(line, '\t');
    if(!strings[0].empty())
      m_outcomes.emplace_back(strings[0]);
    if(!strings[1].empty())
      m_professions.emplace_back(strings[1]);
    if(!strings[2].empty())
      m_recommendationsPos.emplace_back(strings[2]);
    if(!strings[3].empty())
      m_recommendationsNeg.emplace_back(strings[3]);
    if(!strings[4].empty())
      m_recommendationsNeutral.emplace_back(strings[4]);
  }
  dataFile.close();
}

DataManager& DataManager::get()
{
  static DataManager mng;
  return mng;
}

std::string DataManager::getName() const
{
  return getRandom(m_names);
}

std::string DataManager::getRandom(const std::vector<std::string>& in) const
{
  std::vector<std::string> out;
  std::sample(in.begin(), in.end(), std::back_inserter(out), 1, std::mt19937{ std::random_device{}() });
  return *out.begin();
}

std::string DataManager::getProfession() const
{
  return getRandom(m_professions);
}

std::string DataManager::getRecommendationBad() const
{
  return getRandom(m_recommendationsNeg);
}

std::string DataManager::getRecommendationGood() const
{
  return getRandom(m_recommendationsPos);
}

std::string DataManager::getRecommendationNeural() const
{
  return getRandom(m_recommendationsNeg);
}

std::string DataManager::getOutcome() const
{
  return getRandom(m_outcomes);
}

static auto seed = time(0);

int DataManager::getRandomNumber(int min, int max) const
{
  auto rand = std::bind(std::uniform_int_distribution<int>(min, max), std::mt19937(static_cast<unsigned long>(seed++)));
  return rand();
}
