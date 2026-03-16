#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


int main()
{
    //Window
    sf::RenderWindow window(sf::VideoMode({ 640, 480 }), "Aiming Practice", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    //Game Loop
    while (window.isOpen())
    {
        //Event polling
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //Update

        //Render
        window.clear();     // clear old frame
        window.draw(shape); // draw shape
        window.display();   // tell game that the window is done drawing
    }
    
    return 0;
}
