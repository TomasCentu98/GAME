#pragma once
#include <SFML/Graphics.hpp>

class HEROE;

class MAPA : public sf::Drawable, public sf::Transformable {
public:
    MAPA(int, int);
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int, unsigned int);
    bool esCaminable(int x, int y, int width) const;
    bool chequeoPasoDeMapa(HEROE&);
    int *_colisiones;
    int *levelTuto;
    int *level;
    int *levelDos;
    int *levelTres;
    int getMapaActual();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    int _cantAzulejosX;
    int _cantAzulejosY;
    int _mapaActual;
    int _anchoP;
    int _largoP;
};
