#define MAX 15
#include <stdio.h>
#include <stdlib.h>
#include "Menus.h"
#include <curses.h>

int menuInicio (void)
{
	initscr();
	curs_set(0);
	WINDOW* salida = newwin(5,100,4,9);
    refresh();
    box(salida,0,0);
    keypad(salida, TRUE);

    char** opciones = malloc(2 * sizeof(char*));
    for(int i=0; i<2; i++)
    {
    	opciones[i] = malloc(MAX * sizeof(char));
    }
    opciones[0] = "Iniciar sesion";
    opciones[1] = "Registrarse";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
    	for(int i=0; i<2; i++)
    	{
    		if(i==seleccion)
    			wattron(salida, A_REVERSE);
    		mvwprintw(salida, i+1, 1, "%s", opciones[i]);
    		wattroff(salida, A_REVERSE);
    	}
    	wrefresh(salida);

    	eleccion = wgetch(salida);

    	switch(eleccion)
    	{
    		case KEY_UP:
    			seleccion--;
    			if(seleccion == -1)
    				seleccion = 0;
    			break;
    		case KEY_DOWN:
    			seleccion++;
    			if(seleccion == 2)
    				seleccion = 1;
    			break;
    		default:
    			break;
    	}
    	if(eleccion == 10)
    		break;
    }
    werase(salida);
    wrefresh(salida);

   
    if(seleccion == 0)
    	return 0;
    return 1;
}