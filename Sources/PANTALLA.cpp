#include "HEROE.h"
#include "ENEMIGO.h"
#include "MAPA.h"
#include "PANTALLA.h"
#include <iostream>

PANTALLA::PANTALLA() {};

// CREA PANTALLA
void PANTALLA::gameLoop() {

    sf::RenderWindow window(sf::VideoMode({_ANCHO, _LARGO}), "My GAME");
    window.setFramerateLimit(60);

    // MAPA
    MAPA mapa(_ANCHO, _LARGO);

    // DEFINICION E IMAGEN DE OBJETOS
    HEROE entidad;
    entidad.setSprite("IMG/link.png");
    entidad.posicionar(150 , 200);

    ENEMIGO eneg1;
    eneg1.setSprite("IMG/link.png");
    eneg1.posicionar(255.f, 432.f);// hasta {561 , ,432}

    ENEMIGO eneg2;
    eneg2.setSprite("IMG/link.png");
    eneg2.posicionar(465 , 114);
    // {465 , 114}   //hasta   {645 , 114}
    // {465 , 210    //hasta  {645 , 210}

    // GAME LOOP
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        /*
        // PARA SACAR POSICIONES DURANTE EL JUEGO PARA CONFIGURAR
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            std::cout << " X: " << entidad.getSprite().getPosition().x
                        << " Y: " << entidad.getSprite().getPosition().y;
        }
        */

        // MUEVE Y CHEQUEA COLISIONES DEL MAPA
        entidad.actualizar(mapa, _ANCHO, _LARGO);

        if (entidad.estaColisionando(eneg1.getSprite().getPosition())) {
            std::cout << " || Colisionando con ENEG1 || "; // PONER EVENTO DE PELEA
        }

        if (entidad.estaColisionando(eneg2.getSprite().getPosition())) {
            std::cout << " || Colisionando con ENEG2 || "; // PONER EVENTO DE PELEA
        }

        // CONTROLA EL PASO DE MAPAS
        mapa.chequeoPasoDeMapa(entidad);

        // DIBUJO DE ENTIDADES
        window.clear(sf::Color::Black);
        window.draw(mapa);
        window.draw(entidad);

        //if(mapa.getMapaActual() == 1) {
            window.draw(eneg1);
            window.draw(eneg2);
        //}

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
