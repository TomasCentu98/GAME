#include "NPC_aux.h"
#include <cstring>

NPC_aux::NPC_aux() {
};

void NPC_aux::setVida(int vida){
    _vida = vida;
};

void NPC_aux::setFuerza(int fuerza){
    _fuerza = fuerza;
};

int NPC_aux::getFuerza(){
    return _fuerza;
};

int NPC_aux::getVida(){
    return _vida;
};

void NPC_aux::setNombre(const char *nombre){
    strcpy(_nombre, nombre);
};

void NPC_aux::setDialogo(const char *dialogo){
    strcpy(_dialogo, dialogo);
};

char* NPC_aux::getNombre(){
    return _nombre;
};

char* NPC_aux::getDialogo(){
    return _dialogo;
};

void NPC_aux::setSprite(const char *sprite){
    strcpy(_sprite, sprite);
};

char* NPC_aux::getSprite(){
    return _sprite;
}
