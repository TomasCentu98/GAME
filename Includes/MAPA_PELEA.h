#pragma once
#include "MAPA.h"

class MAPA_PELEA {
public:
    MAPA_PELEA();
    std::vector<sf::RectangleShape> getRectangles();
    void setTextureHud(std::string);
    void setTextureFondo(std::string);
    void iniciar();
    sf::Text _textoExplicativo;
    sf::Text _vidaHeroe;
    sf::Text _vidaEnemigo;
private:
    sf::Font _fuentePelea;
    sf::Texture _hudTexture;
    sf::Texture _fondoPelea;
    std::vector<sf::RectangleShape> _cuadros;
};
