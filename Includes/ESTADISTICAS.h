#pragma once

class ESTADISTICAS {

public:
    ESTADISTICAS();

    int generarPuntaje();
    void guardarEstadisticas();
    char* leerEstadisticas();

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
    char* getTotal();

private:
    int _manaUtilizado;
    int _tiempoDeJuego;
    int _danioRecibido;
    int _danioHecho;
    int _vecesDefendido;
    int _vecesCurado;
    char* _nombre;
    char* _total;
};
