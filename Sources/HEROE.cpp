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
    int golpe = calcularGolpe(_fuerza);
    obj.recibirGolpe(golpe);
    _D += golpe;
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
        _vida += 15;
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
    juegoFinalizado = false;
}
/*void HEROE::idlePelea(){

    _textura.loadFromFile("IMG/EnlaceIdle.png");
    _sprite.setTexture(_textura);

    if(relojAnimacion.getElapsedTime().asSeconds()>tiempoAnimacion){
        _sprite.setTextureRect({{0,0},{32,32}});
    }
    if(relojAnimacion.getElapsedTime().asSeconds()>tiempoAnimacion*2){
        _sprite.setTextureRect({{32,0},{32,32}});
        relojAnimacion.restart();
    }
};*/

// para estadisticas
void HEROE::setM(int manaUtilizado) {_M += manaUtilizado;}
void HEROE::setDR(int danioRecibido) {_DR += danioRecibido;}
void HEROE::setD(int daniohecho) {_D = daniohecho;}
void HEROE::setDEF(int vecesDefendido) {_DEF += vecesDefendido;}
void HEROE::setVID(int vecesCurado) {_VID += vecesCurado;}

int HEROE::getM() {return _M;}
int HEROE::getDR() {return _DR;}
int HEROE::getD() {return _D;}
int HEROE::getDEF() {return _DEF;}
int HEROE::getVID() {return _VID;}
