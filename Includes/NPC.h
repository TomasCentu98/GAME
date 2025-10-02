#pragma once
#include "MAPA.h"

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
        void setNombre(std::string);
        std::string getNombre();
        void setDialogo(std::string);
        std::string getDialogo();
        void recibirGolpe(int);
        int calcularGolpe(int);
        /****/
        void actualizar(MAPA&, int, int);
        void patrullar(int, int);
        sf::Vector2f getVelocidad();
        void setVelocidad(float, float);
        bool getDireccionMov();
        void setDirrecionMov(bool);
        bool estaColisionando(sf::Vector2f);
        sf::Sprite getSprite();
        void setSprite(std::string);
        void posicionar(float, float);
        virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    protected:
        bool _estaDefendido;
        int generarFuerza(int);
        const char *_dialogo;
        const char *_nombre;
        int _vida;
        int _fuerza;
    private:
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
        bool _moviendoDerecha = true;
};
