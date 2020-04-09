#include "Usuario.h"
#define numUsuarios 3
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	Usuario *arrayUsuarios;
	arrayUsuarios = (Usuario*) malloc(numUsuarios * sizeof(Usuario));
	
	menu(arrayUsuarios, 5);
	return 0;
}

void menu (Usuario *arrayUsuarios, int tamanyo)
{
	printf("\n1.- Iniciar sesion\n2.- Ver ranking\n3.- JUGAR\n\nQue opcion quieres?\n");
	fflush(stdout);
	char a;
	scanf("%c", &a);
	fflush(stdin);

	switch (a)
	{
		//case '1': iniciarSesion(arrayUsuarios, tamanyo);
		menu(arrayUsuarios, tamanyo);
			break;
		//case '2': verRanking(arrayUsuarios, tamanyo);
		menu(arrayUsuarios, tamanyo);
			break;
		//case '3': jugar();
		menu(arrayUsuarios, tamanyo);
			break;
		case 'q':

			for(int i = 0; i<tamanyo;i++)
			{
				free(arrayUsuarios[i].nombre);   
				free(arrayUsuarios[i].nickname);
				free(arrayUsuarios[i].apellido);
				free(arrayUsuarios[i].puntuaciones);
			}
			free(arrayUsuarios);
			arrayUsuarios = NULL;
			printf("Salida exitosa");
			break;
		default: printf("Introduce 1,2,3 o q\n");
	}
}
