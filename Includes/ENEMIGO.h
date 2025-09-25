#pragma once
#include "NPC.h"
#include "HEROE.h"

class ENEMIGO : public NPC {

    public:
        ENEMIGO();
        void golpear(HEROE &);
        void recibirGolpe(float);
        bool finBatalla();
        sf::Vector2f getVelocidad();
        void setVelocidad(float, float);
        bool getDireccionMov();
        void setDirrecionMov(bool);
    private:
        bool _moviendoDerecha = true;
        sf::Vector2f _spriteSize;
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
};
