#pragma once
#include <SFML/Graphics.hpp>

class PANTALLA
{
public:
    PANTALLA();
    // pantallas
    void gameLoop(HEROE &enlace, sf::RenderWindow &window);
    void creditos(sf::RenderWindow &window);
    void menu(sf::RenderWindow &window);
    void pelea(NPC &rival, HEROE &enlace, sf::RenderWindow &window);
    void cortinaInicio(sf::RenderWindow &window);
    void cortinaFin(sf::RenderWindow &window);
    void tutorial(sf::RenderWindow &, HEROE &);
    unsigned int getAncho();
    unsigned int getLargo();
    ~PANTALLA();

private:
    const unsigned int _ANCHO = 800;
    const unsigned int _LARGO = 576;
};
