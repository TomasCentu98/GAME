#include "../Includes/MAPA.h"
#include "MANAGER.h"

MAPA::MAPA(int anchoP, int largoP) {
    _mapaActual = 1;
    _anchoP = anchoP;
    _largoP = largoP;
    level = copiarDeArchivo("MAPAS/levelUno.txt");
    levelDos = copiarDeArchivo("MAPAS/levelDos.txt");
    levelTres = copiarDeArchivo("MAPAS/levelTres.txt");
    _puertaHaciaLvlDos = {(float)anchoP , 192};
    _puertaVueltaLvlUno = {0 , 224};
    _puertaHaciaLvlTres = {(float)anchoP , 256};
    _puertaVueltaLvlDos = {0 , 224};
    _cantAzulejosX = anchoP / 32;
    _cantAzulejosY = largoP / 32;
    if (load("IMG/map.png", {32, 32}, level.data(), _cantAzulejosX, _cantAzulejosY)) _colisiones = level;
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

void MAPA::chequeoPasoDeMapa(HEROE &entidad) {
    // PUERTA LVL 1
    if (entidad.estaColisionando(_puertaHaciaLvlDos) && _mapaActual == 1) {
        if (load("IMG/map.png", {32 , 32}, levelDos.data(), _cantAzulejosX, _cantAzulejosY)) {
            _colisiones = levelDos;
            entidad.posicionar(32 , 224);
            _mapaActual = 2;
        }
    }

    // PUERTAS LVL 2
    if (entidad.estaColisionando(_puertaVueltaLvlUno) && _mapaActual == 2) {
        if (load("IMG/map.png", {32 , 32}, level.data(), _cantAzulejosX, _cantAzulejosY)) {
            _colisiones = level;
            entidad.posicionar(_anchoP - 32 , 192);
            _mapaActual = 1;
        }
    }
    if (entidad.estaColisionando(_puertaHaciaLvlTres) && _mapaActual == 2) {
        if (load("IMG/map.png", {32 , 32}, levelTres.data(), _cantAzulejosX, _cantAzulejosY)) {
            _colisiones = levelTres;
            entidad.posicionar(32 , 224);
            _mapaActual = 3;
        }
    }

    // PUERTA LVL 3
    if (entidad.estaColisionando(_puertaVueltaLvlDos) && _mapaActual == 3) {
        if (load("IMG/map.png", {32 , 32}, levelDos.data(), _cantAzulejosX, _cantAzulejosY)) {
            _colisiones = levelDos;
            entidad.posicionar(_anchoP - 32 , 256);
            _mapaActual = 2;
        }
    }
}

int MAPA::getMapaActual() {
    return _mapaActual;
}
