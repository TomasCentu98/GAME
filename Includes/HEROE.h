#pragma once
#include "NPC.h"

class HEROE : public NPC {
    public:
        HEROE();
        void curar();
        void hechizo(NPC &);
        void golpear(NPC &);
        void recibirGolpe(float);
        void victoria();
        int getMana();
        void setMana(int);
        void setBatallando(bool);
        bool getBatallando();
        bool vivo=true;
        bool juegoFinalizado=false;
        void resetear();
        int calcularGolpe(int);
        // para estadisticas
        void setM(int);
        void setDR(int);
        void setD(int);
        void setDEF(int);
        void setVID(int);
        int getM();
        int getDR();
        int getD();
        int getDEF();
        int getVID();
        void idlePelea();
        int getVidaMax();
    private:
        bool _enBatalla;
        int _mana;
        int _vidaMax;
        int _exp;
        int _lvl;
        sf::Vector2f _spriteSize;
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
        sf::Clock relojHeroe;
        float tiempoHeroe=1;
        // para estadisticas
        int _M = 0;
        int _DR = 0;
        int _D = 0;
        int _DEF = 0;
        int _VID = 0;
};
