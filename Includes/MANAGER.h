#pragma once
#include <vector>
#include <HEROE.h>

void app();
void turnoHeroe(HEROE &enlace, NPC &rival);
void turnoEnemigo(NPC &rival, HEROE &enlace);
std::vector<int> copiarDeArchivo(const std::string&);
void patrullar(NPC &obj, sf::Vector2f posIzq, sf::Vector2f posDer);
std::string generarDialogo(int numero);
void eventoBatalla(NPC&, HEROE&, sf::RenderWindow&);
