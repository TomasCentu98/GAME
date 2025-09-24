#pragma once
class HEROE;
class ENEMIGO;
#include <SFML/Graphics.hpp>

class MAPA : public sf::Drawable, public sf::Transformable {
public:
    MAPA(int, int);
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int, unsigned int);
    bool esCaminable(int x, int y, int width) const;
    void chequeoPasoDeMapa(HEROE&);
    std::vector<int> _colisiones;
    std::vector<int> level;
    std::vector<int> levelDos;
    std::vector<int> levelTres;
    int getMapaActual();
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray _vertices;
    sf::Texture _tileset;
    sf::Vector2f _puertaHaciaLvlDos;
    sf::Vector2f _puertaVueltaLvlUno;
    sf::Vector2f _puertaHaciaLvlTres;
    sf::Vector2f _puertaVueltaLvlDos;
    int _cantAzulejosX;
    int _cantAzulejosY;
    int _mapaActual;
    int _anchoP;
    int _largoP;
};
