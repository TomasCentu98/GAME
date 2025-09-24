#pragma once

class PANTALLA
{
public:
    PANTALLA();
    void gameLoop();
    float getAncho();
    float getLargo();
    ~PANTALLA();

private:
    const unsigned int _ANCHO = 800;
    const unsigned int _LARGO = 576;
};
