#pragma once

class ESTADISTICAS {

public:
    ESTADISTICAS();

    void generarPuntaje();

    void setM(int);
    void setDR(int);
    void setD(int);
    void setDEF(int);
    void setVID(int);
    void setT(int);
    void setNombre(char*);

    int getM();
    int getDR();
    int getD();
    int getDEF();
    int getVID();
    int getT();
    char* getNombre();
    int getTotal();

    ~ESTADISTICAS();

private:
    int _manaUtilizado;
    int _tiempoDeJuego;
    int _danioRecibido;
    int _danioHecho;
    int _vecesDefendido;
    int _vecesCurado;
    char _nombre[50];
    int _total;
};
