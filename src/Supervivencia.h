#ifndef _SUPERVIVENCIA_H_
#define _SUPERVIVENCIA_H_

#include "Comun.h"
#include "Usuarios.h"

typedef struct 
{
	int x;
	int y;
	int vidas;
} NaveSupervivencia;

typedef struct
{
	int x;
	int y;
} VidaExtra;

void jugarSupervivencia(Usuario* usuarios, int player);

#endif