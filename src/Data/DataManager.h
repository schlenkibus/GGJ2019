#pragma once
#include <vector>
#include <set>
#include <string>

class DataManager
{
 public:
  static DataManager& get();
  int getRandomNumber(int min, int max) const;
  std::string getName() const;
  std::string getProfession() const;
  std::string getOutcome();
  std::string getRecommendationGood();
  std::string getRecommendationBad();
  std::string getRecommendationNeural() const;
  std::string getRandom(const std::vector<std::string>& in) const;
  std::string getRandomDeleting(std::set<std::string>& in);

 protected:
  DataManager();
  std::vector<std::string> m_names;
  std::vector<std::string> m_professions;
  std::vector<std::string> m_outcomesImmutable;
  std::set<std::string> m_outcomesDepleting;
  std::vector<std::string> m_recommendationsPosImmutable;
  std::set<std::string> m_recommendationsPosDepleting;
  std::vector<std::string> m_recommendationsNegImmutable;
  std::set<std::string> m_recommendationsNegDepleting;
  std::vector<std::string> m_recommendationsNeutral;
};
