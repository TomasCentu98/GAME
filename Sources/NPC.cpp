#include <iostream>
#include <cstring>
#include "../Includes/NPC.h"

NPC::NPC(){
    _vida = 100;
    _fuerza = 10;
};

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





