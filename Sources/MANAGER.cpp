#include "MANAGER.h"
#include "PANTALLA.h"
#include <cstring>
#include <stdio.h>
#include <iostream>

using namespace std;

void app() {

    PANTALLA *pantalla = new PANTALLA();

    sf::RenderWindow window(sf::VideoMode({pantalla->getAncho(), pantalla->getLargo()}), "My GAME");
    window.setFramerateLimit(60);
    sf::Image img("IMG/GoblinFrente2.png");
    window.setIcon(img);

    pantalla->menu(window);

    window.close();
    delete pantalla;
}

// lee un .txt y copia la lista de numeros que tenga dentro
int* copiarDeArchivo(const char* nombreArchivo) {

    FILE *archivo = fopen(nombreArchivo, "rb");

    const int CANTIDAD_ARRAY = 475;
    int* listaCopiada = new int[CANTIDAD_ARRAY];

    int numero = 0;

    if (!archivo) {
        return listaCopiada;
        exit(2);
    }

    while(fscanf(archivo, "%d", &listaCopiada[numero]) == 1) {
        numero++;
    }

    fclose(archivo);
    return listaCopiada;
}

char* generarDialogo(int numero){

    FILE *archivo;

    // eligira una linea random del archivo
    int dialogoRandom = (rand()%3)+1;

    if(numero==0)archivo = fopen("DialogosEnemigo.txt","rb");
    if(numero==1)archivo = fopen("DialogosHeroe.txt","rb");

    if(archivo==nullptr){
        exit(1);
    }

    char dialogoEnArchivo[200]={};
    int contador=1;

    while(fgets(dialogoEnArchivo, sizeof(dialogoEnArchivo), archivo)){
        if(contador==dialogoRandom){
            break;
        }
        contador++;

        // limpia la linea de caracteres para que no haya sobrantes en la siguiente
        memset(dialogoEnArchivo, '\0', sizeof(dialogoEnArchivo));
    };

    fclose(archivo);

    return dialogoEnArchivo;
}
