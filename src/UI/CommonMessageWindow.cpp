#include "CommonMessageWindow.h"
#include "../ResourceManager.h"
#include "../Application.h"

CommonMessageWindow::CommonMessageWindow(const std::string &message, const std::string& header) :
    GenericWindow(message, header, ResourceManager::get().getTexture("message.png")),
    ok{Application::get().getMidPoint() + sf::Vector2f(0, 250),
        []() {
            Application::get().getLevel().closeMessage();
        },
        "Okay!"}
{
}

void CommonMessageWindow::draw(sf::RenderWindow &window) {
    GenericWindow::draw(window);
    ok.draw(window);
}

void CommonMessageWindow::onEvent(sf::Event &e) {
    ok.onEvent(e);
    GenericWindow::onEvent(e);
}
