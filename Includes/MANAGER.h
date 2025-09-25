#pragma once
#include <fstream>
#include <vector>
#include <HEROE.h>
#include <ENEMIGO.h>

void app();
void turnoHeroe(HEROE &enlace, ENEMIGO &rival);
void turnoEnemigo(ENEMIGO &rival, HEROE &enlace);
std::vector<int> copiarDeArchivo(const std::string&);
void patrullar(ENEMIGO &obj, sf::Vector2f posIzq, sf::Vector2f posDer);
