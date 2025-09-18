#pragma once
#include <SFML/Graphics.hpp>
/// CLASE BASE NPC
class NPC : public sf::Drawable {
    public:
        NPC();
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
        void setSprite(std::string);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void actualizar();
        bool estaColisionando(sf::Vector2f areaObj);
        sf::Sprite getSprite();
        void posicionar(float, float);
    protected:
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
