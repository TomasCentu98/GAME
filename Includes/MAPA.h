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
    const float _ANCHO = 1280;
    const float _LARGO = 720;


};
