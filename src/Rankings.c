#include "Usuarios.h"
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"


void liberarMemoriaRankingClasico (Usuario* arrayusuarios, int size, Usuario* aux, WINDOW* rankingClasico)
{
	/*for (int i=0; i<size; i++)
	{
		free(arrayusuarios[i].nickname);
		arrayusuarios[i].nickname = NULL;
		free(arrayusuarios[i].contrasenya);
		arrayusuarios[i].contrasenya = NULL;
		free(arrayusuarios[i].puntuaciones);
		arrayusuarios[i].puntuaciones = NULL;
	}
	free(arrayusuarios);
	arrayusuarios = NULL;*/

	free(aux->nickname);
	aux->nickname = NULL;
	free(aux->contrasenya);
	aux->contrasenya = NULL;
	free(aux->puntuaciones);
	aux->puntuaciones = NULL;


	werase(rankingClasico);
    erase();
    wrefresh(rankingClasico);
    refresh();
 
    //endwin();
}

void rankingClasico (Usuario* usuarios, int size)
{
	Usuario* arrayUsuarios;
	arrayUsuarios = (Usuario*) malloc (size * sizeof(Usuario));
    for (int i=0; i<size; i++)
    {
        arrayUsuarios[i] = usuarios[i];
    }

	Usuario* aux = (Usuario*) malloc (sizeof(Usuario));
	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size-1; j++)
		{
			if (arrayUsuarios[j].puntuaciones[0] < arrayUsuarios[j+1].puntuaciones[0])
			{
				*(aux) = arrayUsuarios[j];
				arrayUsuarios[j] = arrayUsuarios[j+1];
				arrayUsuarios[j+1] = *(aux);
			}
		}
	}

	noecho();
	move(9, 43);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(1));
    printw("  RANKING CLASICO  ");
    attroff(COLOR_PAIR(1));
    WINDOW* rankingClasico = newwin(1.5*size,100,10,9);
    box(rankingClasico,0,0);
    refresh();
    wrefresh(rankingClasico);

    int posicion = 1;
    for (int i=0; i<size; i++)
    {
    	wmove(rankingClasico, posicion+i, 1); wprintw(rankingClasico, "%d.- %s", (i+1), arrayUsuarios[i].nickname);
    	wmove(rankingClasico, posicion+i, 28); wprintw(rankingClasico, "%.2f", arrayUsuarios[i].puntuaciones[0]);
    	wmove(rankingClasico, posicion+i, 36); wprintw(rankingClasico, "puntos");
    }

    wrefresh(rankingClasico);

    move(9,75);
    attron(A_REVERSE);
    printw("pulsa enter para volver..");
    attroff(A_REVERSE);

   

    int auxi = getch();
    if (auxi == 10)
    	liberarMemoriaRankingClasico(arrayUsuarios, size, aux, rankingClasico);
}