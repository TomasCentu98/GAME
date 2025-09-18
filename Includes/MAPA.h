#pragma once
#include <SFML/Graphics.hpp>

class MAPA : public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int, unsigned int);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::VertexArray _vertices;
    sf::Texture _tileset;
};
