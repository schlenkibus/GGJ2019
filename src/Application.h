#pragma once


#include <SFML/Graphics/RenderWindow.hpp>

class Application {
protected:
    Application();
    sf::RenderWindow window;
public:
    static Application& get();
    void run();
};
