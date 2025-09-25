#include "../Includes/ENEMIGO.h"

ENEMIGO::ENEMIGO() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    _vida = 100.f;
    _fuerza = 15.f;

    _sprite.setOrigin({
        _sprite.getTexture().getSize().x / 2.f,
        _sprite.getTexture().getSize().y / 2.f
    });
}

void ENEMIGO::golpear(HEROE &heroe) {
    heroe.recibirGolpe(calcularGolpe(_fuerza));
}

void ENEMIGO::recibirGolpe(float cantGolpe) {
    _vida -= cantGolpe;
}

bool ENEMIGO::finBatalla() {
    if (_vida <= 0) return true;

    return false;
}

sf::Vector2f ENEMIGO::getVelocidad() {
    return _velocidad;
}

void ENEMIGO::setVelocidad(float x, float y) {
    _velocidad.x = x;
    _velocidad.y = y;
}

void ENEMIGO::setDirrecionMov(bool derecha) {
    _moviendoDerecha = derecha;
}

bool ENEMIGO::getDireccionMov() {
    return _moviendoDerecha;
}
