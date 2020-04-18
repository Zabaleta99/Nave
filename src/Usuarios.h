#ifndef SRC_USUARIO_H_
#define SRC_USUARIO_H_
#include <stdio.h>

typedef struct
{
	char* nickname;
	char* contrasenya;
	float* puntuaciones;
} Usuario;


Usuario* leerUsuarios(FILE *file, int *size);
void escribirUsuarios(Usuario *usuarios, int size);


#endif
