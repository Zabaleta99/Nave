#include "Usuarios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50

void vaciar (char aux []);

Usuario * leerUsuarios (FILE *file, int *size)
{
	char aux[MAX];
	char c = '\0';

	fgets(aux, MAX, file);
	sscanf(aux, "%d", size);

	Usuario *arrayUsuarios = (Usuario *) malloc (*size * sizeof(Usuario));

	for (int i=0; !feof(file); i++)
	{
		c = '\0';
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
		vaciar(aux);

		c = '\0';

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
		vaciar(aux);
	}

	return arrayUsuarios;
}

void vaciar (char aux [])
{
	for (int i=0; i<50; i++)
	{
		aux[i] = '\0';
	}
}