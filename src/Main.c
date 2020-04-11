#include "Usuarios.h"
#include "Menus.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 15

int main(void)
{
	FILE *file = fopen("Usuarios.txt", "r");
	if (file == NULL)
	{
		printf("Error al abrir el fichero Usuarios.txt\n");
		fflush(stdout);
		return -1;
	}
	int *size = malloc(sizeof(int));

	Usuario * arrayUsers;
	arrayUsers = leerUsuarios(file, size);

	for (int i=0; i<*size; i++)
	{
		printf("Nombre: %s   Contra: %s\n", (arrayUsers+i)->nickname, (arrayUsers+i)->contrasenya);
		fflush(stdout);
	}
	

	

	int opcion = menuInicio();

	if (opcion == 0)
	{
		//iniciar sesion
	}

	if (opcion == 1)
	{
		//registrarse
	}

	return 0;
}