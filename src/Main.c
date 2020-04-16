#include "Usuarios.h"
#include "Menus.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 15
#include <windows.h> //brrar
void menuMain();

int main(void)
{
	menuMain();
}

void menuMain()
{
	FILE *file = fopen("Usuarios.txt", "r");
	if (file == NULL)
	{
		printf("Error al abrir el fichero Usuarios.txt\n");
		fflush(stdout);
		exit(-1);
	}
	int *size = malloc(sizeof(int));

	Usuario * arrayUsers;
	arrayUsers = leerUsuarios(file, size);

	/*for (int i=0; i<*size; i++)
	{
		printf("Nombre: %s   Contra: %s\n", (arrayUsers+i)->nickname, (arrayUsers+i)->contrasenya);
		fflush(stdout);
	}
	printf(":::::::::::::::::::::::::::::\n");
	fflush(stdout);
	Sleep(6000);*/

	int opcion = menuInicio();
	Usuario *user;

	if (opcion == 0)
	{
		user = menuIniciarSesion(arrayUsers, *size);
		int selected = menuPlayer(user);

		while (selected != 4)
		{

			if (selected == 0)
			{

			}
			else if (selected == 1)
			{
				jugarClasico();
				selected = menuPlayer(user);
			}
			else if (selected == 2)
			{

			}
			else if (selected == 3)
			{
				
			}

			else if (selected == 4)
			{
				menuMain();
			}
		}
	}

	if (opcion == 1)
	{
		menuRegistrarse(arrayUsers, *size);
	}
}