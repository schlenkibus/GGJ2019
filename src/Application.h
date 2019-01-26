#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Level.h"

class Application {
public:
    static Application& get();
    void run();
    sf::Vector2i getMouse() const;
    Level& getLevel();
    void quit();
protected:
    Application();
    sf::RenderWindow window;
    Level level;
};
