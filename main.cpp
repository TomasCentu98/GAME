#include <iostream>
#include "MANAGER.h"
#include <ctime>
#include <iostream>
/*
#include "HEROE.h"
#include "ENEMIGO.h"
#include "MANAGER.h"
*/

int main () {

    sf::RenderWindow window(sf::VideoMode({800,576}), "SFML works!");

    sf::Texture tex("IMG/menu.png");
    sf::Sprite image(tex);

sf::RectangleShape jugar( {160.f , 40.f} );
    jugar.setOutlineThickness(2.5);
    jugar.setOutlineColor(sf::Color::Black);
    jugar.setFillColor(sf::Color::Transparent);
    jugar.setPosition( {350.f , 410.f} );
sf::RectangleShape creditos( {160.f , 40.f} );
    creditos.setOutlineThickness(2.5);
    creditos.setOutlineColor(sf::Color::Black);
    creditos.setFillColor(sf::Color::Transparent);
    creditos.setPosition( {350.f , 459.f} );
sf::RectangleShape salir( {160.f , 40.f} );
    salir.setOutlineThickness(2.5);
    salir.setOutlineColor(sf::Color::Black);
    salir.setFillColor(sf::Color::Transparent);
    salir.setPosition( {350.f , 505.f} );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if(jugar.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y})){
                app();
            } if(creditos.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y})){

            } if(salir.getGlobalBounds().contains({(float) mousePos.x ,  (float) mousePos.y})){
                exit(1);
            }
           }
        window.clear();
        window.draw(image);
        window.draw(jugar);
        window.draw(creditos);
        window.draw(salir);
        window.display();
    }




    return 0;


}
