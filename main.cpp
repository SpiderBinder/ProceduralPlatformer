#include <iostream>
#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{
    /*sf::RenderWindow window(sf::VideoMode(
        sf::VideoMode::getDesktopMode().width, 
        sf::VideoMode::getDesktopMode().height),
        "Platformer",
        sf::Style::Fullscreen);*/

    sf::RenderWindow window(sf::VideoMode(800, 500), "Platformer");
    //window.setVerticalSyncEnabled(true);

    Game game(window);
    if (!game.Init())
        return 0;

    sf::Clock clock;

    while (window.isOpen())
    {
        // Checking window events
        sf::Event event;
        // Calculating deltatime
        sf::Time time = clock.restart();
        float dt = time.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
                game.KeyboardEvent(event);
            if (event.type == sf::Event::MouseButtonPressed)
                game.MouseEvent(event);
            
        }

        game.Update(dt);

        window.clear(sf::Color::Cyan);
        game.Render();
        window.display();
    }

    return 0;
}