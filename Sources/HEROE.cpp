#include "../Includes/HEROE.h"

HEROE::HEROE() :
    _textura("IMG/GoblinFrente2.png"),
    _sprite(_textura)
{
    _vida = 150;
    _fuerza = 15;
    _exp = 0;
    _lvl = 1;
    _mana = 100;
    _enBatalla = false;

}

void HEROE::setMana(int mana) {
    _mana = mana;
}

bool HEROE::getBatallando() {
    return _enBatalla;
}

void HEROE::setBatallando(bool estaPeleando) {
    _enBatalla = estaPeleando;
}

void HEROE::golpear(NPC &obj) {
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
            _vida+=20;
            if(_vida>100){
                _vida=100;
            }
        }
        _mana -= 20;
    }
}

void HEROE::hechizo(NPC &rival){
    if(_mana >= 30){
        rival.recibirGolpe(_fuerza*1.4);
    }
    _mana -=30;
}

int HEROE::getMana(){
    return _mana;
}

void HEROE::resetear(){
   _vida = 150;
    _fuerza = 15;
    _exp = 0;
    _lvl = 1;
    _mana = 100;
    _enBatalla = false;
    vivo = true;
}

