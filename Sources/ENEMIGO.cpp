#include "../Includes/ENEMIGO.h"

ENEMIGO::ENEMIGO() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    _vida = 150.f;
    _fuerza = 15.f;
}

void ENEMIGO::golpear(HEROE heroe) {
    heroe.recibirGolpe(calcularGolpe(_fuerza));
}

void ENEMIGO::recibirGolpe(float cantGolpe) {
    _vida = cantGolpe;
}

bool ENEMIGO::finBatalla() {
    if (_vida <= 0) return true;

    return false;
}
