#include "../Includes/MAPA.h"
#include "MANAGER.h"
#include <cstring>

MAPA::MAPA(int anchoP, int largoP) {
    _mapaActual = 0;
    _anchoP = anchoP;
    _largoP = largoP;
    levelTuto = copiarDeArchivo("MAPAS/levelTuto.txt");
    level = copiarDeArchivo("MAPAS/levelUno.txt");
    levelDos = copiarDeArchivo("MAPAS/levelDos.txt");
    levelTres = copiarDeArchivo("MAPAS/levelTres.txt");
    _cantAzulejosX = anchoP / 32;
    _cantAzulejosY = largoP / 32;
    if (load("IMG/map.png", {32, 32}, levelTuto, _cantAzulejosX, _cantAzulejosY)) _colisiones = levelTuto;
}

bool MAPA::load(const std::filesystem::path& path, sf::Vector2u azulejosSize, const int* azulejos, unsigned int width, unsigned int height) {

    if (!_tileset.loadFromFile(path)) return false;

    _vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    _vertices.resize(width * height * 6);

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            const int azulejosN = azulejos[i + j * width];

            const int tu = azulejosN % (_tileset.getSize().x / azulejosSize.x);
            const int tv = azulejosN / (_tileset.getSize().x / azulejosSize.x);

            sf::Vertex* triangles = &_vertices[(i + j * width) * 6];

            triangles[0].position = sf::Vector2f(i * azulejosSize.x, j * azulejosSize.y);
            triangles[1].position = sf::Vector2f((i + 1) * azulejosSize.x, j * azulejosSize.y);
            triangles[2].position = sf::Vector2f(i * azulejosSize.x, (j + 1) * azulejosSize.y);
            triangles[3].position = sf::Vector2f(i * azulejosSize.x, (j + 1) * azulejosSize.y);
            triangles[4].position = sf::Vector2f((i + 1) * azulejosSize.x, j * azulejosSize.y);
            triangles[5].position = sf::Vector2f((i + 1) * azulejosSize.x, (j + 1) * azulejosSize.y);

            triangles[0].texCoords = sf::Vector2f(tu * azulejosSize.x, tv * azulejosSize.y);
            triangles[1].texCoords = sf::Vector2f((tu + 1) * azulejosSize.x, tv * azulejosSize.y);
            triangles[2].texCoords = sf::Vector2f(tu * azulejosSize.x, (tv + 1) * azulejosSize.y);
            triangles[3].texCoords = sf::Vector2f(tu * azulejosSize.x, (tv + 1) * azulejosSize.y);
            triangles[4].texCoords = sf::Vector2f((tu + 1) * azulejosSize.x, tv * azulejosSize.y);
            triangles[5].texCoords = sf::Vector2f((tu + 1) * azulejosSize.x, (tv + 1) * azulejosSize.y);
        }

    }

    return true;
}

void MAPA::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    states.transform *= getTransform();

    states.texture = &_tileset;

    target.draw(_vertices, states);
}

bool MAPA::esCaminable(int x, int y, int width) const {
    const int index = x + y * width;
    if(index >= 450) return false;
    return _colisiones[index];
}

bool MAPA::chequeoPasoDeMapa(HEROE &entidad) {

    sf::Vector2f ubicacion = entidad.getSprite().getPosition();

    if (ubicacion.x > _anchoP - 16)
    {

        if (_mapaActual == 0) {
            entidad.posicionar(ubicacion.x - (_anchoP - 128)  , ubicacion.y);
            if (load("IMG/map.png", {32 , 32}, level, _cantAzulejosX, _cantAzulejosY)) {
                _colisiones = level;
                _mapaActual = 1;
                return true;
            }
        }

        if (_mapaActual == 1) {
            entidad.posicionar(ubicacion.x - (_anchoP - 32)  , ubicacion.y);
            if (load("IMG/map.png", {32 , 32}, levelDos, _cantAzulejosX, _cantAzulejosY)) {
                _colisiones = levelDos;
                _mapaActual = 2;
                return true;
            }
        }

        if (_mapaActual == 2) {
            entidad.posicionar(ubicacion.x - (_anchoP - 32)  , ubicacion.y);
            if (load("IMG/map.png", {32 , 32}, levelTres, _cantAzulejosX, _cantAzulejosY)) {
                _colisiones = levelTres;
                _mapaActual = 3;
                return true;
            }
        }
    }

    if (ubicacion.x < 16)
    {
        if (_mapaActual == 2) {
            entidad.posicionar(ubicacion.x + (_anchoP + 32) , ubicacion.y);
            if (load("IMG/map.png", {32 , 32}, level, _cantAzulejosX, _cantAzulejosY)) {
                _colisiones = level;
                _mapaActual = 1;
                return true;
            }
        }

        if (_mapaActual == 3) {
            entidad.posicionar(ubicacion.x + (_anchoP + 32) , ubicacion.y);
            if (load("IMG/map.png", {32 , 32}, levelDos, _cantAzulejosX, _cantAzulejosY)) {
                _colisiones = levelDos;
                _mapaActual = 2;
                return true;
            }
        }
    }

    return false;
}

int MAPA::getMapaActual() {
    return _mapaActual;
}
