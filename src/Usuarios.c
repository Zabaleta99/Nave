#include "Usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

Usuario * leerUsuarios (FILE *file, int *size)
{
	char aux[MAX];
	vaciar(aux);
	char c;

	fgets(aux, MAX, file);
	sscanf(aux, "%d", size);

	Usuario *arrayUsuarios = (Usuario *) malloc (*size * sizeof(Usuario));

	for (int i=0; !feof(file); i++)
	{
		for (int j=0; c!=';'; j++)
		{
			c = fgetc(file);

			if(c != ';')
			{
				aux[j] = c;
			}
		}

		(arrayUsuarios + i)->nickname = (char *) malloc ((strlen(aux)+1) * sizeof (char));
		sscanf(aux, "%s", (arrayUsuarios+i)->nickname);

		for (int k=0; (c != '\n') && (!feof(file)); k++)
		{
			c = fgetc(file);
			if ((c != '\n') && (!feof(file)))
			{
				aux[k] = c;
			}
		}

		(arrayUsuarios + i)->contrasenya = (char *) malloc ((strlen(aux)+1) * sizeof (char));
		sscanf(aux, "%s", (arrayUsuarios+i)->contrasenya);
	}
	fclose(file);
	return arrayUsuarios;
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
			fprintf(file, "%s;%s", usuarios[i].nickname, usuarios[i].contrasenya);
		}

		else
		{
			fprintf(file, "%s;%s\n", usuarios[i].nickname, usuarios[i].contrasenya);
		}
	}
	fclose(file);
}