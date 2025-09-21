#include "../Includes/MANAGER.h"
#include "../Includes/PANTALLA.h"
#include <iostream>
using namespace std;

void app() {

   PANTALLA pantalla;

   pantalla.gameLoop();

}

void turnoHeroe(HEROE &enlace, ENEMIGO &rival){
    int decision;
    cout << "//Tu turno//" << endl;
    cout << "Salud enemiga: " << rival.getVida() << endl;
    cout << "Tu salud: " <<enlace.getVida() << endl;
    cout << "Tu mana: " <<enlace.getMana() << endl;
    cout << "Golpear // 1 | Defender // 2 | Curar // 3  | Hechizo // 4" << endl;
    cin >> decision;

    switch(decision){
        case 1:
            cout << "Golpeando" << endl << endl ;
            enlace.golpear(rival);
            break;
        case 2:
            cout << "Te defiendes, en el proximo golpe recibiras menos danio" << endl << endl;
            enlace.setDefensa(true);
            break;
        case 3:
            cout << "Utilizas un hechizo de curacion" << endl << endl;
            enlace.curar();
            break;
        case 4:
            cout << "Utilizas un hechizo ofensivo" << endl << endl;
            enlace.hechizo(rival);
            break;
    }
}

void turnoEnemigo(ENEMIGO &rival, HEROE &enlace){
    int decisionRival;
    cout << "||Turno del rival||" << endl << endl;
    cout << "Salud enemiga: " << rival.getVida() << endl << endl;
    cout << "Tu salud: " <<enlace.getVida() << endl << endl;

    cout << "El rival esta decidiendo su accion" << endl;
    decisionRival = (rand() % 2) + 1;

    if(decisionRival==1){
    cout << "El rival esta atacando" << endl << endl;
    rival.golpear(enlace);
    }
    else{
    cout << "El rival se esta defendiendo" << endl << endl;
    rival.setDefensa(true);
    }
}

// lee un .txt y copia la lista de numeros que tenga dentro
std::vector<int> copiarDeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    std::vector<int> listaCopiada;
    int numero;

    if (!archivo.is_open()) {
        return listaCopiada;
    }

    while (archivo >> numero) {
        listaCopiada.push_back(numero);
    }

    archivo.close();
    return listaCopiada;

}


