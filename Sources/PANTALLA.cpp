#include "HEROE.h"
#include "ENEMIGO.h"
#include "MAPA.h"
#include "PANTALLA.h"
#include "MANAGER.h"

PANTALLA::PANTALLA() {};

// CREA PANTALLA E INICIA JUEGO
void PANTALLA::gameLoop() {

    sf::RenderWindow window(sf::VideoMode({_ANCHO, _LARGO}), "My GAME");
    window.setFramerateLimit(60);

    // MAPA
    MAPA mapa(_ANCHO, _LARGO);

    // DEFINICION E IMAGEN DE OBJETOS
    HEROE entidad;
    entidad.setSprite("IMG/link.png");
    entidad.posicionar(561 , 432);

    ENEMIGO eneg1pan1;
    eneg1pan1.setSprite("IMG/link.png");
    //eneg1pan1.posicionar(255.f, 432.f);// hasta {561 ,432}

    ENEMIGO eneg2pan1;
    eneg2pan1.setSprite("IMG/link.png");
    //eneg2pan1.posicionar(465 , 114);
    // {465 , 114}   //hasta   {645 , 114}
    // {465 , 210    //hasta  {645 , 210}

    ENEMIGO eneg1pan2;
    eneg1pan2.setSprite("IMG/link.png");

    ENEMIGO eneg2pan2;
    eneg2pan2.setSprite("IMG/link.png");

    ENEMIGO gefe;
    gefe.setSprite("IMG/link.png");

    bool enemigosCreadosPan1 = false;
    bool enemigosCreadosPan2 = false;
    bool enemigosCreadosPan3 = false;

    // GAME LOOP
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // MOVIMIENTO DE ENTIDADES
        entidad.actualizar(mapa, _ANCHO, _LARGO);


        if (!entidad.estaColisionando(eneg1pan1.getSprite().getPosition())) {
            patrullar(eneg1pan1, {250,432}, {562,432});
            if (entidad.estaColisionando(eneg1pan1.getSprite().getPosition()))
            {
                eventoBatalla(eneg1pan1, entidad);
            }
        }
        if (!entidad.estaColisionando(eneg2pan1.getSprite().getPosition())) {
            patrullar(eneg2pan1, {250,114}, {465,114});
            if (entidad.estaColisionando(eneg2pan1.getSprite().getPosition())){
                eventoBatalla(eneg2pan1, entidad);
            }
        }
        if (!entidad.estaColisionando(eneg1pan2.getSprite().getPosition())) {
            patrullar(eneg1pan2, {200,432}, {550,432});
            if (entidad.estaColisionando(eneg1pan2.getSprite().getPosition())){
                eventoBatalla(eneg1pan2, entidad);
            }
        }
        if (!entidad.estaColisionando(eneg2pan2.getSprite().getPosition())) {
            patrullar(eneg2pan2, {300,114}, {600,114});
            if (entidad.estaColisionando(eneg2pan2.getSprite().getPosition())){
                eventoBatalla(eneg2pan2, entidad);
            }
        }
        if (!entidad.estaColisionando(gefe.getSprite().getPosition())) {
            // PONER EVENTO DE PELEA GEFE
           //if(entidad.estaColisionando(gefe.getSprite().getPosition()))
        }

        // CONTROLA EL PASO DE MAPAS
        mapa.chequeoPasoDeMapa(entidad);

        // DIBUJO DE ENTIDADES
        window.clear(sf::Color::Black);
        window.draw(mapa);
        window.draw(entidad);

        // PARA REEUBICAR ENEMIGOS AL CAMBIAR MAPA
        if(mapa.getMapaActual() == 1 && !enemigosCreadosPan1) {
            gefe.posicionar(-32,-32);
            eneg1pan2.posicionar(-32,-32);
            eneg2pan2.posicionar(-32,-32);
            eneg1pan1.posicionar(255, 432);
            eneg2pan1.posicionar(465 , 114);
            //
            enemigosCreadosPan1 = true;
            enemigosCreadosPan2 = false;
            enemigosCreadosPan3 = false;
        }
        if(mapa.getMapaActual() == 2 && !enemigosCreadosPan2) {
            gefe.posicionar(-32,-32);
            eneg1pan2.posicionar(200, 432);
            eneg2pan2.posicionar(465 , 150);
            eneg1pan1.posicionar(-32,-32);
            eneg2pan1.posicionar(-32,-32);
            //
            enemigosCreadosPan1 = false;
            enemigosCreadosPan2 = true;
            enemigosCreadosPan3 = false;
        }
        if(mapa.getMapaActual() == 3 && !enemigosCreadosPan3) {
            gefe.posicionar(300,300);
            eneg1pan2.posicionar(-32,-32);
            eneg2pan2.posicionar(-32,-32);
            eneg1pan1.posicionar(-32,-32);
            eneg2pan1.posicionar(-32,-32);
            //
            enemigosCreadosPan1 = false;
            enemigosCreadosPan2 = false;
            enemigosCreadosPan3 = true;
        }

        window.draw(eneg1pan1);
        window.draw(eneg2pan1);
        window.draw(eneg1pan2);
        window.draw(eneg2pan2);
        window.draw(gefe);

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
