#include "../Includes/MAPA.h"

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

bool MAPA::esSolido(int x, int y, int width) const {
    const int index = x + y * width;
    if(index >= 450) return false;
    return _colisiones[index];
}
