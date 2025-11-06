#include "ESTADISTICAS.h"
#include <cstring>

ESTADISTICAS::ESTADISTICAS() { }

void ESTADISTICAS::generarPuntaje() {
    int primerTermino = _manaUtilizado + _danioHecho + _tiempoDeJuego;
    int segundoTermino = _vecesDefendido + _vecesCurado + _danioRecibido;
    int calculo = (primerTermino * 2 - segundoTermino) / _tiempoDeJuego;
    int resultado = calculo * 1000;

    if (resultado < 0) {
        resultado *= -1;
    }

    _total = resultado;
}

void ESTADISTICAS::setM(int mana) {_manaUtilizado = mana;}

void ESTADISTICAS::setDR(int danioRecibido) {_danioRecibido = danioRecibido;}

void ESTADISTICAS::setD(int danioHecho) {_danioHecho = danioHecho;}

void ESTADISTICAS::setDEF(int vecesDefendido) {_vecesDefendido = vecesDefendido;}

void ESTADISTICAS::setVID(int vecesCurado) {_vecesCurado = vecesCurado;}

void ESTADISTICAS::setT(int tiempoDeJuego) {_tiempoDeJuego = tiempoDeJuego;}

void ESTADISTICAS::setNombre(char* nombre) {strcpy(_nombre, nombre);}

int ESTADISTICAS::getM() {return _manaUtilizado;}

int ESTADISTICAS::getDR() {return _danioRecibido;}

int ESTADISTICAS::getD() {return _danioHecho;}

int ESTADISTICAS::getDEF() {return _vecesDefendido;}

int ESTADISTICAS::getVID() {return _vecesCurado;}

int ESTADISTICAS::getT() {return _tiempoDeJuego;}

char* ESTADISTICAS::getNombre() {return _nombre;}

int ESTADISTICAS::getTotal() {return _total;}

ESTADISTICAS::~ESTADISTICAS() { }
