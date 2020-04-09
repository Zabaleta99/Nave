#ifndef SRC_USUARIO_H_
#define SRC_USUARIO_H_

typedef struct
{
	char *nombre;
	char *apellido;
	char *nickname;
	int *puntuaciones;
	int mejorPuntuacion;
} Usuario;

void introducirUsuario (Usuario *arrayUsuarios, int size);
void mejorPuntuacion (Usuario *arrayUsuarios, int size);


#endif
