#pragma once
#include <vector>
#include <HEROE.h>
#include "ESTADISTICAS.h"

void app();
int* copiarDeArchivo(const char* nombreArchivo);
char* generarDialogo(int numero);
char* dialogosTuto(int numero);
NPC leerEnemigo();
void guardarEstadisticas(ESTADISTICAS est);
ESTADISTICAS* leerEstadisticas();
