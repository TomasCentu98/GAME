#pragma once
class ENEMIGO;
#include "NPC.h"
#include "ENEMIGO.h"

class HEROE : public NPC {
    public:
        HEROE();
        void curar();
        void hechizo(ENEMIGO &);
        void golpear(ENEMIGO &);
        void recibirGolpe(float);
        void victoria();
        int getMana();

    private:
        int _mana;
        int _exp;
        int _lvl;
        sf::Vector2f _spriteSize;
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
};
