#include <SFML/Graphics.hpp>
#include "../Includes/MAPA.h"
void pantalla()
{
    sf::Clock clock;
    const int ancho = 800;
    const int largo = 600;
    sf::RenderWindow window(sf::VideoMode({ancho, largo}), "My GAME");

    /// DEFINICION E IMAGEN DEL PERSONAJE
    sf::Texture personaje_textura("IMG/link.png");
    personaje_textura.setSmooth(true);
    sf::Sprite personaje(personaje_textura);

    /// GAME LOOP
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        /// EVITA QUE SE VAYA DE PANTALLA
        if(personaje.getPosition().x < 0) {
            personaje.setPosition({0.f, personaje.getPosition().y});
        }
        if(personaje.getPosition().y < 0) {
            personaje.setPosition({personaje.getPosition().x, 0.f});
        }
        if(personaje.getPosition().x > ancho - 50.f) {
            personaje.setPosition({ancho-50.f, personaje.getPosition().y});
        }
        if(personaje.getPosition().y > largo - 50.f) {
            personaje.setPosition({personaje.getPosition().x, largo-50.f});
        }

        /// MOVIMIENTO CON TECLADO
        float velocidadPersonaje = 150.f;
        float delta = clock.restart().asSeconds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            personaje.move({0.f, -(velocidadPersonaje * delta)});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            personaje.move({-(velocidadPersonaje * delta), 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            personaje.move({0, velocidadPersonaje * delta});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            personaje.move({velocidadPersonaje * delta, 0});
        }

        window.clear(sf::Color::Black);

        /// TODO VISUAL
        window.draw(personaje);




        window.display();
    }
}
