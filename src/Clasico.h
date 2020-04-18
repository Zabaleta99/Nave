#ifndef _CLASICO_H_
#define _CLASICO_H_

#include "Comun.h"
#include "Usuarios.h"

typedef struct 
{
	int x;
	int y;
	int vidas;
	int corazones;
} NaveClasico;

typedef struct 
{
	int x;
	int y;
}Bala;

void jugarClasico(Usuario* usuarios, int player);

#endif