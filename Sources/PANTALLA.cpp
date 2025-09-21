#include "HEROE.h"
#include "ENEMIGO.h"
#include "MAPA.h"
#include "PANTALLA.h"
#include "MANAGER.h"
#include <fstream>

PANTALLA::PANTALLA() {};

// CREA PANTALLA
void PANTALLA::gameLoop() {

    sf::RenderWindow window(sf::VideoMode({_ANCHO, _LARGO}), "My GAME");
    window.setFramerateLimit(60);
    const int cantAzulejosX = _ANCHO / 32;
    const int cantAzulejosY = _LARGO / 32;
    int mapaActual = 1;

    std::vector<int> level = copiarDeArchivo("MAPAS/levelUno.txt");
    sf::Vector2f salidaLevelUno = {_ANCHO,192};
    std::vector<int> levelDos = copiarDeArchivo("MAPAS/levelDos.txt");
    std::vector<int> levelTres = copiarDeArchivo("MAPAS/levelTres.txt");

    // crea mapa con dos texturas
    // 0 = no caminable // 1 = caminable
    MAPA map;
    if (!map.load("IMG/map.png", {32, 32}, level.data(), cantAzulejosX, cantAzulejosY));
    map._colisiones = level;

    // DEFINICION E IMAGEN DEL PERSONAJE
    HEROE entidad;
    entidad.setSprite("IMG/link.png");
    entidad.posicionar(64.f, 128.f);
    sf::FloatRect entidadEspacio = entidad.getSprite().getGlobalBounds();

    ENEMIGO gil;
    gil.setSprite("IMG/link.png");
    gil.posicionar(200.f, 128.f);

    // GAME LOOP
    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        entidad.actualizar(map, _ANCHO, _LARGO);

        if (entidadEspacio.contains(gil.getSprite().getGlobalBounds().getCenter())) {
            // EVENTO AL CHOCAR CON ENTIDAD
        }

        // HACER IF POR CADA MAPA ACTUAL
        if (entidad.getSprite().getGlobalBounds().contains(salidaLevelUno)) {
            if (!map.load("IMG/map.png", {32, 32}, levelDos.data(), cantAzulejosX, cantAzulejosY));
            map._colisiones = levelDos;
            entidad.posicionar(0, 288);
        }


        window.clear(sf::Color::Black);

        window.draw(map);
        window.draw(entidad);
        window.draw(gil);

        window.display();

        // audio
    }
};

float PANTALLA::getAncho() {
    return _ANCHO;
};

float PANTALLA::getLargo() {
    return _LARGO;
};

PANTALLA::~PANTALLA() {};
