#pragma once
#include "MAPA.h"
#include <SFML/Graphics.hpp>

/// CLASE BASE NPC
class NPC : public sf::Drawable {
    public:
        NPC();
        bool getDefensa();
        void golpear(HEROE &);
        void setDefensa(bool);
        int defensa();
        void setVida (int);
        void setFuerza (int);
        int getVida();
        int getFuerza();
        void setNombre(const char *);
        char * getNombre();
        void setDialogo(const char *);
        char * getDialogo();
        void recibirGolpe(int);
        int calcularGolpe(int);
        /****/
        void actualizar(MAPA&, int, int, sf::Clock);
        void patrullar(int, int);
        sf::Vector2f getVelocidad();
        void setVelocidad(float, float);
        bool getDireccionMov();
        void setDirrecionMov(bool);
        bool estaColisionando(sf::Vector2f);
        sf::Sprite getSprite();
        void setSprite(const char *);
        void posicionar(float, float);
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    protected:
        bool _estaDefendido = false;
        int generarFuerza(int);
        char _dialogo[200] = {};
        char _nombre[50] = {};
        int _vida;
        int _fuerza;
    private:
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
        bool _moviendoDerecha = true;
};
