#include "../Includes/HEROE.h"

HEROE::HEROE() :
    _textura("IMG/link.png"),
    _sprite(_textura)
{
    _vida = 100;
    _fuerza = 10;
    _exp = 0;
    _lvl = 1;
    _mana = 70;
}

void HEROE::golpear(ENEMIGO &obj) {
    obj.recibirGolpe(calcularGolpe(_fuerza));
}

void HEROE::recibirGolpe(float cantGolpe) {
    _vida -= cantGolpe;
}

void HEROE::victoria() {
    _exp += 25;

    if (_exp >= 50) {
        _exp = 0;
        _lvl++;
        _fuerza += 3;
        _vida += 10;
    }
}

void HEROE::curar(){
    if(_mana >=20){
        if(_vida<100){
            _vida+=15;
        if(_vida>100){
            _vida=100;
        }
        }
        _mana -= 20;
    }
}

void HEROE::hechizo(ENEMIGO &rival){
if(_mana >= 30){
    if(!rival.getDefensa()){
        rival.recibirGolpe(_fuerza*1.3);
    }
   else{rival.recibirGolpe((_fuerza*1.3)-rival.defensa());
   }
   _mana -=30;
}
}
int HEROE::getMana(){
    return _mana;
};

