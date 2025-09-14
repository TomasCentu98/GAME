#pragma once

class NPC {
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

    protected:
        void golpear();
        void recibirGolpe(float);

    private:
        const char *_dialogo;
        const char *_nombre;
        float _vida;
        float _fuerza;
};

