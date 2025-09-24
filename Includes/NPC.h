#pragma once
#include "MAPA.h"

/// CLASE BASE NPC
class NPC : public sf::Drawable {
    public:
        NPC();
        bool getDefensa();
        void setDefensa(bool);
        int defensa();
        void setVida (float);
        void setFuerza (float);
        float getVida();
        float getFuerza();
        void setNombre(std::string);
        std::string getNombre();
        void setDialogo(std::string);
        std::string getDialogo();
        void recibirGolpe(float);
        float calcularGolpe(float);
        /****/
        void actualizar(MAPA &, int, int);
        bool estaColisionando(sf::Vector2f areaObj);
        sf::Sprite getSprite();
        void setSprite(std::string);
        void posicionar(float, float);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    protected:
        bool _estaDefendido;
        float generarFuerza(float);
        const char *_dialogo;
        const char *_nombre;
        float _vida;
        float _fuerza;
    private:
        sf::Sprite _sprite;
        sf::Texture _textura;
        sf::Vector2f _velocidad;
};
