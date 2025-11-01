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
        void resetear();
    private:
        bool _enBatalla;
        int _mana;
        int _exp;
        int _lvl;
        sf::Vector2f _spriteSize;
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
};
