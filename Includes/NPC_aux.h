#pragma once

class NPC_aux {
public:
    NPC_aux();
    void setVida(int);
    void setFuerza(int);
    int getVida();
    int getFuerza();
    void setNombre(const char *);
    void setDialogo(const char *);
    char * getNombre();
    char * getDialogo();
    void setSprite(const char *);
    char * getSprite();
private:
    char _dialogo[200] = {};
    char _nombre[50] = {};
    char _sprite[100] = {};
    int _vida;
    int _fuerza;
};
