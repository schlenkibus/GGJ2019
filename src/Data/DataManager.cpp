#include <iosfwd>
#include <fstream>
#include <iostream>
#include <sstream>
#include "DataManager.h"

DataManager::DataManager()
{
  auto names = std::ifstream("../src/Data/names_formatted");
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

  auto dataFile = std::ifstream("../src/Data/characters.tsv");
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

  std::cout << "\nNames:\n";
  for(auto& name : m_names)
  {
    std::cout << name << '\n';
  }

  std::cout << "\nOutcomes:\n";
  for(auto& outcome : m_outcomes)
  {
    std::cout << outcome << '\n';
  }

  std::cout << "\nProfession:\n";
  for(auto& profession : m_professions)
  {
    std::cout << profession << '\n';
  }

  std::cout << "\nRecommendations Good:\n";
  for(auto& rec : m_recommendationsPos)
  {
    std::cout << rec << '\n';
  }

  std::cout << "\nRecommendations Bad:\n";
  for(auto& rec : m_recommendationsNeg)
  {
    std::cout << rec << '\n';
  }

  std::cout << "\nRecommendations Neural:\n";
  for(auto& rec : m_recommendationsNeutral)
  {
    std::cout << rec << '\n';
  }
}

DataManager& DataManager::get()
{
  static DataManager mng;
  return mng;
}
