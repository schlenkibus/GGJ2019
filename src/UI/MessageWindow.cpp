#include "MessageWindow.h"
#include "../ResourceManager.h"
#include "../Application.h"

MessageWindow::MessageWindow(const std::string &message, const std::string& header) :
DrawableObject(ResourceManager::get().getTexture("message.png"), Application::get().getMidPoint()),
m_header{header, ResourceManager::get().getFont()},
m_message{message, ResourceManager::get().getFont()},
closeButton{Application::get().getMidPoint() + sf::Vector2f(0, 250), [](){
        Application::get().getLevel().closeMessage();
    }, "Okay!"} {

    std::string perm;
    auto lastInsertAgo = 0;

    for(auto c: message) {
        if(std::isspace(c)) {
            if(lastInsertAgo >= 15) {
                perm += '\n';
                lastInsertAgo = 0;
                continue;
            }
        }
        perm += c;
        lastInsertAgo++;
    }

    m_message.setString(perm);

    m_header.setPosition(Application::get().getMidPoint() + sf::Vector2f(-135, -250));
    m_message.setPosition(Application::get().getMidPoint() + sf::Vector2f(-135, -200));
    m_message.setOutlineThickness(2);
    m_message.setOutlineColor(sf::Color::Black);
    m_message.setFillColor(sf::Color::White);
}

void MessageWindow::draw(sf::RenderWindow &window) {
    DrawableObject::draw(window);
    window.draw(m_header);
    window.draw(m_message);
    closeButton.draw(window);
}

void MessageWindow::onEvent(sf::Event &e) {
    closeButton.onEvent(e);
}
