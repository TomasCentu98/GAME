#include "MAPA_PELEA.h"
#include "vector"

MAPA_PELEA::MAPA_PELEA() :
    _hudTexture(),
    _fondoPelea(),
    _fuentePelea("MAPAS/fuentePelea.ttf"),
    _textoExplicativo(_fuentePelea),
    _vidaEnemigo(_fuentePelea),
    _vidaHeroe(_fuentePelea)
{}

std::vector<sf::RectangleShape> MAPA_PELEA::getRectangles() {
    return _cuadros;
}

void MAPA_PELEA::setTextureHud(std::string path) {
    _hudTexture.loadFromFile(path);
}

void MAPA_PELEA::setTextureFondo(std::string path) {
    _fondoPelea.loadFromFile(path);
}

void MAPA_PELEA::iniciar() {
    sf::Vector2f tamBotones = {130.f , 30.f};
    sf::Color baseIntColor(20.f , 50.f , 20.f , 150.f);

    for (int i = 0; i < 8; ++i) {
        _cuadros.push_back(sf::RectangleShape());
    }
    //FONDO
    _cuadros[0].setSize({800.f , 576.f});
    _cuadros[0].setTexture(&_fondoPelea);
    //BASE HUD
    _cuadros[1].setSize({500.f , 200.f});
    _cuadros[1].setFillColor(baseIntColor);
    _cuadros[1].setPosition({150.f , 350.f});
    //CUADRO TEXTO
    _cuadros[2].setSize({315.f , 70.f});
    _cuadros[2].setOutlineThickness(2.5);
    _cuadros[2].setFillColor(baseIntColor);
    _cuadros[2].setPosition({315.f , 365.f});
    //IMG HUD PERSONAJE
    _cuadros[3].setSize({150.f , 180.f});
    _cuadros[3].setTexture(&_hudTexture);
    _cuadros[3].setPosition({160.f , 360.f});
    //PEGAR
    _cuadros[4].setSize(tamBotones);
    _cuadros[4].setFillColor(sf::Color::Transparent);
    _cuadros[4].setPosition({170.f , 380.f});
    //DEFENZA
    _cuadros[5].setSize(tamBotones);
    _cuadros[5].setFillColor(sf::Color::Transparent);
    _cuadros[5].setPosition({170.f , 415.f});
    //CURAR
    _cuadros[6].setSize(tamBotones);
    _cuadros[6].setFillColor(sf::Color::Transparent);
    _cuadros[6].setPosition({170.f , 450.f});
    //HECHIZO
    _cuadros[7].setSize(tamBotones);
    _cuadros[7].setFillColor(sf::Color::Transparent);
    _cuadros[7].setPosition({170.f , 485.f});

    _textoExplicativo.setPosition({320.f , 370.f});
    _textoExplicativo.setCharacterSize(12);

    _vidaHeroe.setString("asd");
    _vidaHeroe.setCharacterSize(12);
    _vidaHeroe.setPosition({350.f , 470.f});

    _vidaEnemigo.setString("asd");
    _vidaEnemigo.setCharacterSize(12);
    _vidaEnemigo.setPosition({500.f , 470.f});
}
