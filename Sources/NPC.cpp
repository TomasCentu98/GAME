#include <iostream>
#include "../Includes/NPC.h"
#include "../Includes/MAPA.h"

NPC::NPC() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    _sprite.setOrigin({_sprite.getTexture().getSize().x / 2.f, _sprite.getTexture().getSize().y / 2.f});

    _vida = 100.f;
    _fuerza = 5.f;
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

    // EVITA QUE SALGA DE PANTALLA

    // PANTALLA IZQUIERDA
    if(_sprite.getGlobalBounds().getCenter().x < _sprite.getOrigin().x) {
        _sprite.setPosition({_sprite.getOrigin().x, _sprite.getPosition().y});
    }
    // PANTALLA ARRIBA
    if(_sprite.getGlobalBounds().getCenter().y < _sprite.getOrigin().y) {
        _sprite.setPosition({_sprite.getPosition().x, _sprite.getOrigin().y});
    }
    // PANTALLA ABAJO
    if(_sprite.getGlobalBounds().getCenter().y > screen->getLargo() - _sprite.getOrigin().y) {
        _sprite.setPosition({_sprite.getPosition().x , screen->getLargo() - _sprite.getOrigin().y});
    }
    // PANTALLA DERECHA
    if(_sprite.getGlobalBounds().getCenter().x > screen->getAncho() - _sprite.getOrigin().x) {
        _sprite.setPosition({screen->getAncho() - _sprite.getOrigin().x , _sprite.getPosition().y});
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




