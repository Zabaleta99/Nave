#include "Usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

Usuario* leerUsuarios (FILE *file, int *size)
{
	char* linea = malloc(MAX * sizeof(char));
	char** items = malloc(4 * sizeof(char*));

	fgets(linea, MAX, file);
	sscanf(linea, "%d", size);

	Usuario *usuarios = (Usuario*) malloc(*size * sizeof(Usuario));

	int contador = 0;
	while(fgets(linea, MAX, file))
	{
		char* token = strtok(linea, ";");
		int i=0;
		while(token != NULL)
		{
			items[i] = token;
			token = strtok(NULL, ";");
			i++;
		}
		usuarios[contador].nickname = malloc((strlen(items[0])+1) * sizeof(char));
		strcpy(usuarios[contador].nickname, items[0]);
		usuarios[contador].contrasenya = malloc((strlen(items[1])+1) * sizeof(char));
		strcpy(usuarios[contador].contrasenya, items[1]);
		usuarios[contador].puntuaciones = malloc(2 * sizeof(float));
		usuarios[contador].puntuaciones[0] = strtof(items[2], NULL);
		usuarios[contador].puntuaciones[1] = strtof(items[3], NULL);
		contador++;
	}
	free(linea);
	linea = NULL;
	free(items);
	items = NULL;
	return usuarios;
}

void escribirUsuarios(Usuario *usuarios, int size)
{
	FILE *file = fopen("Usuarios.txt", "w");
	if (file == NULL)
	{
		printf("Error al abrir el fichero Usuarios.txt\n");
		fflush(stdout);
		exit(-1);
	}

	fprintf(file, "%d\n", size);

	for (int i=0; i<size; i++)
	{
		if (i == size-1)
		{
			fprintf(file, "%s;%s;%0.2f;%0.2f", usuarios[i].nickname, usuarios[i].contrasenya, usuarios[i].puntuaciones[0], usuarios[i].puntuaciones[1]);
		}

		else
		{
			fprintf(file, "%s;%s;%0.2f;%0.2f\n", usuarios[i].nickname, usuarios[i].contrasenya, usuarios[i].puntuaciones[0], usuarios[i].puntuaciones[1]);
		}
	}
	fclose(file);
	free(file);
	file = NULL;
}