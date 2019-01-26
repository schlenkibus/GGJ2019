#pragma once
#include <vector>
#include <string>

class DataManager
{
 public:
  static DataManager& get();

 protected:
  DataManager();
  std::vector<std::string> m_names;
  std::vector<std::string> m_professions;
  std::vector<std::string> m_outcomes;
  std::vector<std::string> m_recommendationsPos;
  std::vector<std::string> m_recommendationsNeg;
  std::vector<std::string> m_recommendationsNeutral;


};
