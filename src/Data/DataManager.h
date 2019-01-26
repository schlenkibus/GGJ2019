#pragma once
#include <vector>
#include <string>

class DataManager
{
 public:
  static DataManager& get();
  int getRandomNumber(int min, int max) const;
  std::string getName() const;
  std::string getProfession() const;
  std::string getOutcome() const;
  std::string getRecommendationGood() const;
  std::string getRecommendationBad() const;
  std::string getRecommendationNeural() const;
  std::string getRandom(const std::vector<std::string>& in) const;

 protected:
  DataManager();
  std::vector<std::string> m_names;
  std::vector<std::string> m_professions;
  std::vector<std::string> m_outcomes;
  std::vector<std::string> m_recommendationsPos;
  std::vector<std::string> m_recommendationsNeg;
  std::vector<std::string> m_recommendationsNeutral;
};
