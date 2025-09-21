#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "rlutil.h"
#include "HEROE.h"
#include "ENEMIGO.h"
#include "MANAGER.h"
using namespace std;


int main(){
    std::srand(std::time(nullptr));
    HEROE* enlace=new HEROE;
    ENEMIGO* rival=new ENEMIGO;

    while(rival->finBatalla()==false){
    turnoHeroe(*enlace, *rival);
    turnoEnemigo(*rival, *enlace);
    }
return 0;
}
