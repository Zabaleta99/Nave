#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"
#include "Usuarios.h"
static int MAX_X;
static int MAX_Y;

void liberarMemoriaRankingClasico (Usuario* arrayusuarios, Usuario* aux, WINDOW* rankingClasico)
{
	free(arrayusuarios);
	arrayusuarios = NULL;

	free(aux);
	aux = NULL;
	
	wclear(rankingClasico);
    wrefresh(rankingClasico);
    delwin(rankingClasico);
    clear();
    refresh();
}

void liberarMemoriaRankingSupervivencia(Usuario* arrayusuarios, Usuario* aux, WINDOW* rankingSupervivencia)
{
	free(arrayusuarios);
	arrayusuarios = NULL;

	free(aux);
	aux = NULL;
	
	wclear(rankingSupervivencia);
    wrefresh(rankingSupervivencia);
    delwin(rankingSupervivencia);
    clear();
    refresh();
}

void rankingClasico (Usuario* usuarios, int size)
{
    getmaxyx(stdscr, MAX_Y, MAX_X);
	Usuario* arrayUsuarios = (Usuario*) malloc (size * sizeof(Usuario));
    for (int i=0; i<size; i++)
    {
        arrayUsuarios[i] = usuarios[i];
    }

	Usuario* aux = (Usuario*) malloc (sizeof(Usuario));
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-i-1; j++)
		{
			if (arrayUsuarios[j].puntuaciones[0] < arrayUsuarios[j+1].puntuaciones[0])
			{
				*aux = arrayUsuarios[j];
				arrayUsuarios[j] = arrayUsuarios[j+1];
				arrayUsuarios[j+1] = *aux;
			}
		}
	}

	noecho();
	move((MAX_Y/2)-(1.5*size)/2-1, MAX_X/4);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(1));
    printw("  RANKING CLASICO  ");
    attroff(COLOR_PAIR(1));
    WINDOW* rankingClasico = newwin(1.5*size,MAX_X/2,(MAX_Y/2)-(1.5*size)/2,MAX_X/4);
    box(rankingClasico,0,0);
    refresh();
    wrefresh(rankingClasico);

    for (int i=0; i<size && i<10; i++)
    {
    	mvwprintw(rankingClasico, 1+i, 1, "%d.- %s", (i+1), arrayUsuarios[i].nickname);
    	mvwprintw(rankingClasico, 1+i, 28, "%.2f", arrayUsuarios[i].puntuaciones[0]);
    	mvwprintw(rankingClasico, 1+i, 36, "puntos");
    }

    wrefresh(rankingClasico);

    move((MAX_Y/2)+(1.5*size)/2+1,MAX_X/4);
    attron(A_REVERSE);
    printw("pulsa enter para volver...");
    attroff(A_REVERSE);

    while(getch()!= 10);
    liberarMemoriaRankingClasico(arrayUsuarios, aux, rankingClasico);
}

void rankingSupervivencia(Usuario* usuarios, int size)
{
    getmaxyx(stdscr, MAX_Y, MAX_X);
	Usuario* arrayUsuarios = (Usuario*) malloc (size * sizeof(Usuario));
    for (int i=0; i<size; i++)
    {
        arrayUsuarios[i] = usuarios[i];
    }

	Usuario* aux = (Usuario*) malloc (sizeof(Usuario));
	for (int i=0; i<size-1; i++)
	{
		for (int j=0; j<size-i-1; j++)
		{
			if (arrayUsuarios[j].puntuaciones[1] < arrayUsuarios[j+1].puntuaciones[1])
			{
				*aux = arrayUsuarios[j];
				arrayUsuarios[j] = arrayUsuarios[j+1];
				arrayUsuarios[j+1] = *aux;
			}
		}
	}

	noecho();
	move((MAX_Y/2)-(1.5*size)/2-1,MAX_X/4);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(1));
    printw("  RANKING SUPERVIVENCIA  ");
    attroff(COLOR_PAIR(1));
    WINDOW* rankingSupervivencia = newwin(1.5*size,MAX_X/2,(MAX_Y/2)-(1.5*size)/2,MAX_X/4);
    box(rankingSupervivencia,0,0);
    refresh();
    wrefresh(rankingSupervivencia);

    for (int i=0; i<size && i<10; i++)
    {
    	mvwprintw(rankingSupervivencia, 1+i, 1, "%d.- %s", (i+1), arrayUsuarios[i].nickname);
    	mvwprintw(rankingSupervivencia, 1+i, 28, "nivel");
    	mvwprintw(rankingSupervivencia, 1+i, 36, "%.0f", arrayUsuarios[i].puntuaciones[1]);
    }

    wrefresh(rankingSupervivencia);

    move((MAX_Y/2)+(1.5*size)/2+1,MAX_X/4);
    attron(A_REVERSE);
    printw("pulsa enter para volver...");
    attroff(A_REVERSE);

    while(getch()!= 10);
    liberarMemoriaRankingSupervivencia(arrayUsuarios, aux, rankingSupervivencia);
}