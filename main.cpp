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
    std::srand(std::time(nullptr));
    //app();

    sf::RenderWindow window(sf::VideoMode({800, 576}), "My GAME");
    window.setFramerateLimit(60);

    // RECTANGULOS PARA BASE DE INTERFAZ DE PELEA
    sf::RectangleShape baseInterfaz({500.f , 200.f});
    baseInterfaz.setOutlineThickness(2.5);
    baseInterfaz.setOutlineColor(sf::Color::Black);
    sf::Color baseIntColor(20.f , 50.f , 20.f , 150.f);
    baseInterfaz.setFillColor(baseIntColor);
    baseInterfaz.setPosition({150.f , 350.f});

    sf::RectangleShape vidaHeroe({150.f , 80.f});
    vidaHeroe.setOutlineThickness(2.f);
    vidaHeroe.setOutlineColor(sf::Color::Green);
    vidaHeroe.setFillColor(sf::Color::Transparent);
    vidaHeroe.setPosition({315.f , 450.f});

    sf::RectangleShape vidaEnemigo({150.f , 80.f});
    vidaEnemigo.setOutlineThickness(2.f);
    vidaEnemigo.setOutlineColor(sf::Color::Green);
    vidaEnemigo.setFillColor(sf::Color::Transparent);
    vidaEnemigo.setPosition({480.f , 450.f});

    sf::RectangleShape textoPelea({315.f , 70.f});
    textoPelea.setOutlineThickness(2.f);
    textoPelea.setOutlineColor(sf::Color::Green);
    textoPelea.setFillColor(sf::Color::Transparent);
    textoPelea.setPosition({315.f , 365.f});

    sf::RectangleShape hud({150.f , 180.f});
    sf::Texture* hudTexture = new sf::Texture("IMG/HUD_batalla.png");
    hud.setTexture(hudTexture);
    hud.setPosition({160.f , 360.f});

    // FONDO DE PANTALLA DE PELEA
    sf::RectangleShape fondo({800.f , 576.f});
    sf::Texture* fondoPelea = new sf::Texture("IMG/fondoPelea.png");
    fondo.setTexture(fondoPelea);

    // TEXTOS PARA INTERFAZ
    sf::Font fuentePelea("MAPAS/fuentePelea.ttf");
    sf::Text textoAtaque(fuentePelea, "hola0");
    textoAtaque.setPosition({300.f, 200.f});
    sf::Text textoDefenza(fuentePelea, "hola1");
    sf::Text textoCuracion(fuentePelea, "hola2");
    sf::Text textohechizo(fuentePelea, "hola3");

    // TIPO DE CURSOR
    const sf::Cursor cursor = sf::Cursor::createFromSystem(
                                sf::Cursor::Type::Hand).value();

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Mostrar la posición en consola
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::cout << "//x: " << mousePos.x;
            std::cout << " //y: " << mousePos.y << std::endl;
        }

        window.clear(sf::Color::Black);
        window.draw(fondo);
        window.draw(baseInterfaz);
        window.draw(hud);
        window.draw(vidaHeroe);
        window.draw(vidaEnemigo);
        window.draw(textoPelea);

        //window.draw(textoAtaque);
        //window.draw(textoDefenza);
        //window.draw(textoCuracion);
        //window.draw(textohechizo);

        window.setMouseCursor(cursor);
        window.display();
    }

    return 0;


}
