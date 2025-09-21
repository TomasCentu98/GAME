#include <iostream>
#include "MANAGER.h"
#include <ctime>
/*
#include "HEROE.h"
#include "ENEMIGO.h"
#include "MANAGER.h"
*/

int main () {
    std::srand(std::time(nullptr));
    app();

    /*
    HEROE* enlace = new HEROE;
    ENEMIGO* rival = new ENEMIGO;

    while(rival->finBatalla()==false){
        turnoHeroe(*enlace, *rival);
        turnoEnemigo(*rival, *enlace);
    }

    */


    return 0;
}
