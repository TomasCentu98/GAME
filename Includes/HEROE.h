#pragma once
class ENEMIGO;
#include "NPC.h"
#include "ENEMIGO.h"

class HEROE : public NPC {
    public:
        HEROE();
        void golpear(ENEMIGO*);
        void recibirGolpe(float);
        void victoria();
    private:
        int _exp;
        int _lvl;
        sf::Vector2f _spriteSize;
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
};
