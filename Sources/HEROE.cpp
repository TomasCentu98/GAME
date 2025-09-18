#include "../Includes/HEROE.h"

HEROE::HEROE() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    _vida = 100.f;
    _fuerza = 10.f;
    _exp = 0;
    _lvl = 1;
}

void HEROE::golpear(ENEMIGO *obj) {
    obj->recibirGolpe(calcularGolpe(_fuerza));
}

void HEROE::recibirGolpe(float cantGolpe) {
    _vida -= cantGolpe;
}

void HEROE::victoria() {
    _exp += 25;

    if (_exp >= 100) {
        _exp = 0;
        _lvl++;
    }
}
