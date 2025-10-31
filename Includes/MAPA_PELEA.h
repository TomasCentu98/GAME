#pragma once
#include <SFML/Graphics.hpp>

class MAPA_PELEA {
public:
    MAPA_PELEA();
    sf::RectangleShape* getRectangles();
    void setTextureHud(std::string);
    void setTextureFondo(std::string);
    void iniciar();
    std::string getTexto();
    void setTexto(std::string);
    std::string getVidaHeroe();
    void setVidaHeroe(std::string);
    std::string getVidaEnemigo();
    void setVidaEnemigo(std::string);

    sf::Text getTxt();
    sf::Text getE();
    sf::Text getH();
private:
    sf::Text _textoExplicativo;
    sf::Text _vidaHeroe;
    sf::Text _vidaEnemigo;
    sf::Font _fuentePelea;
    sf::Texture _hudTexture;
    sf::Texture _fondoPelea;
    sf::RectangleShape* _cuadros = new sf::RectangleShape[8];
};
