#include <iostream>
#include "../Includes/NPC.h"
#include "../Includes/MAPA.h"

NPC::NPC() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    sf::Vector2f spriteSize(_sprite.getTexture().getSize());
    _spriteSize = spriteSize;
    _sprite.setOrigin({_spriteSize.x / 2.f, _spriteSize.y / 2.f});

    _vida = 100.f;
    _fuerza = 1.f;
}

void NPC::setVida (float vida){
    _vida = vida;
};

void NPC::setFuerza (float fuerza){
    _fuerza = fuerza;
};

float NPC::getVida(){
    return _vida;
};

float NPC::getFuerza(){
    return _fuerza;
};

void NPC::setNombre(std::string nombre){
    _nombre = nombre.data();
};

std::string NPC::getNombre(){
    std::string nombre(_nombre);
    return nombre;
};

void NPC::setDialogo(std::string dialogo){
    _dialogo = dialogo.data();
};

std::string NPC::getDialogo(){
    std::string dialogo(_dialogo);
    return dialogo;
};

// DATOS PARA VIDEO

void NPC::setSprite(std::string txt) {
    _textura.loadFromFile(txt),
    _sprite.setTexture(_textura, true);
}

void NPC::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

void NPC::actualizar() {
    _velocidad = {0, 0};

    PANTALLA* screen = new PANTALLA;
    float espX = screen->getAncho() - _spriteSize.x;
    float espY = screen->getLargo() - _spriteSize.y;

    // EVITA QUE SALGA DE PANTALLA
    if(_sprite.getGlobalBounds().getCenter().x < _sprite.getOrigin().x) {
        _sprite.setPosition({_sprite.getOrigin().x, _sprite.getPosition().y});
    }
    if(_sprite.getGlobalBounds().getCenter().y < _sprite.getOrigin().y) {
        _sprite.setPosition({_sprite.getPosition().x, _sprite.getOrigin().y});
    }
    if(_sprite.getGlobalBounds().getCenter().x  > espX) {
        _sprite.setPosition({espX, _sprite.getPosition().y});
    }
    if(_sprite.getGlobalBounds().getCenter().y > espY) {
        _sprite.setPosition({_sprite.getPosition().x, espY});
    }

    // TECLAS DE MOVIMIENTO
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
       _velocidad.y = -5;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        _velocidad.x = -5;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
       _velocidad.y = 5;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        _velocidad.x = 5;
    }

    // DIRECCION DE SPRITE AL CAMINAR
    if (_velocidad.x < 0) {
        _sprite.setScale({-1.f, 1.f});
    } else if (_velocidad.x > 0) {
        _sprite.setScale({1.f,1.f});
    }

    _sprite.move(_velocidad);
}




