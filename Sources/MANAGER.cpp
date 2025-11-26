#include "MANAGER.h"
#include "PANTALLA.h"
#include "NPC_aux.h"
#include <cstring>
#include <stdio.h>

using namespace std;

void app() {

    PANTALLA *pantalla = new PANTALLA();

    sf::RenderWindow window(sf::VideoMode({pantalla->getAncho(), pantalla->getLargo()}), "My GAME");
    window.setFramerateLimit(60);
    sf::Image img("IMG/DragFrente2.png");
    window.setIcon(img);

    HEROE *enlace = new HEROE();
    enlace->setSprite("IMG/Enlace.png");
    enlace->setNombre("Enlace");
    enlace->setDialogo("hola");

    pantalla->menu(window,*enlace);

    window.close();

    delete pantalla;
    delete enlace;
}

// lee un .txt y copia la lista de numeros que tenga dentro
int* copiarDeArchivo(const char* nombreArchivo) {

    FILE *archivo = fopen(nombreArchivo, "rb");

    const int CANTIDAD_ARRAY = 475;
    int* listaCopiada = new int[CANTIDAD_ARRAY];

    int numero = 0; // para saber cuantos numeros hay en el archivo

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
    if(numero==3)archivo = fopen("tutorial.txt", "rb");

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

char* dialogosTuto(int dialogo){

    FILE *archivo = fopen("tutorial.txt", "rb");

    if(archivo==nullptr) exit(1);

    const int TAM_BUFFER = 350;
    char* dialogoEnArchivo = new char[TAM_BUFFER];
    int dialogoActual = 0;

    while (fgets(dialogoEnArchivo, TAM_BUFFER, archivo)) {
        if (dialogoActual == dialogo) break;
        dialogoActual++;
    }

    fclose(archivo);

    return dialogoEnArchivo;
}

void leerEnemigo(NPC &enemigo) {

    FILE *archivo;

    if (enemigo.getRango()) { archivo = fopen("jefe.dat", "rb"); }
    else { archivo = fopen("enemigos.dat", "rb"); }

    if(archivo==nullptr) return;

    NPC_aux enemigoAux;

    if (!enemigo.getRango()) {
        int enemigoEnArchivo = (rand()%4);
        fseek(archivo, sizeof(NPC_aux) * enemigoEnArchivo, SEEK_SET);
    }

    if (enemigo.getRango()) {
        fread(&enemigoAux, sizeof(NPC_aux), 1, archivo);
        enemigo.setNombre(enemigoAux.getNombre());
        enemigo.setDialogo(enemigoAux.getDialogo());
        enemigo.setSprite("IMG/DragFrente2.png");
        enemigo.setVida(enemigoAux.getVida());
        enemigo.setFuerza(enemigoAux.getFuerza());
    } else {
        fread(&enemigoAux, sizeof(NPC_aux), 1, archivo);
        enemigo.setNombre(enemigoAux.getNombre());
        enemigo.setDialogo(enemigoAux.getDialogo());
        enemigo.setSprite("IMG/goblin.png");
        enemigo.setVida(enemigoAux.getVida());
        enemigo.setFuerza(enemigoAux.getFuerza());
    }

    fclose(archivo);
}


void guardarEstadisticas(ESTADISTICAS est) {
    FILE* file = fopen("estadisticas.dat", "ab");

    if (file == nullptr) exit(1);

    fwrite(&est, sizeof(ESTADISTICAS), 1, file);

    fclose(file);
}

