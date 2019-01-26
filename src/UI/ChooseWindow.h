#pragma once
#include "GenericWindow.h"
#include "../tools/ResourceManager.h"

template <class Option> class ChooseWindow : public GenericWindow
{
 public:
  typedef std::tuple<Option, Option, Option> tOptionTuple;

  explicit ChooseWindow(tOptionTuple&& options);
  void draw(sf::RenderWindow& window) override;
  bool onEvent(sf::Event& e) override;

 protected:
  tOptionTuple m_options;
};

template <class Option>
ChooseWindow<Option>::ChooseWindow(ChooseWindow::tOptionTuple&& options)
    : GenericWindow("Choose One Of Those:", "Choose!", ResourceManager::get().getTexture("message.png"))
    , m_options{ std::move(options) }
{
}

template <class Option> void ChooseWindow<Option>::draw(sf::RenderWindow& window)
{
  GenericWindow::draw(window);
  std::get<0>(m_options).draw(window);
  std::get<1>(m_options).draw(window);
  std::get<2>(m_options).draw(window);
}

template <class Option> bool ChooseWindow<Option>::onEvent(sf::Event& e)
{
  if(std::get<0>(m_options).onEvent(e))
    return true;
  if(std::get<1>(m_options).onEvent(e))
    return true;
  if(std::get<2>(m_options).onEvent(e))
    return true;

  return GenericWindow::onEvent(e);
}