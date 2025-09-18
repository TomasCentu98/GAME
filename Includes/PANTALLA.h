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
    const float _ANCHO = 800;
    const float _LARGO = 576;


};
