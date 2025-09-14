#include "../Includes/NPC.h"
#include "../Includes/MAPA.h"

/// CONSTRUCTOR DEFAULT
PANTALLA::PANTALLA() { };

/// CREA PANTALLA
void PANTALLA::gameLoop() {

    sf::RenderWindow window(sf::VideoMode({_ANCHO, _LARGO}), "My GAME");
    window.setFramerateLimit(60);

    // DEFINICION E IMAGEN DEL PERSONAJE
    NPC entidad;
    entidad.setSprite("IMG/link.png");

    // GAME LOOP
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        entidad.actualizar();

        window.clear(sf::Color::Black);
        window.draw(entidad);
        window.display();
    }
};

float PANTALLA::getAncho() {
    return _ANCHO;
};


float PANTALLA::getLargo() {
    return _LARGO;
};

PANTALLA::~PANTALLA() {};
