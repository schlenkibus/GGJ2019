#include <SFML/Window/Event.hpp>
#include "Application.h"
#include "Level.h"

Application& Application::get() {
    static Application app;
    return app;
}

Application::Application() : window{sf::VideoMode(1366, 768), "GGJ19", sf::Style::Fullscreen} {
}

void Application::run() {
    sf::Event event{};

    Level level;
    sf::Clock clock;

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    exit(0);
                    break;
                default:
                    level.onEvent(event);
                    break;
            }
        }

        auto delta = clock.getElapsedTime().asMilliseconds();
        level.update(delta);
        clock.restart();

        window.clear();
        level.draw(window);
        window.display();
    }
}
