#ifndef SRC_USUARIO_H_
#define SRC_USUARIO_H_
#include <stdio.h>

typedef struct
{
	char *nickname;
	char *contrasenya;
	int *puntuaciones;
	int mejorPuntuacion;
} Usuario;


Usuario * leerUsuarios (FILE *file, int *size);



#endif
