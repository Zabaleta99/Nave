#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include "Supervivencia.h"
#define ALTO 3
#define IZQUIERDA 2
#define BAJO 19
#define DERECHA 95
#define MAX_AST 15
#define MAX_EXTRA 5
#define MAX_LENGHT 15



void mostrarNivel(int* num_ast)
{
	WINDOW* nivel = newwin(5,21,12,50);
	refresh();
	box(nivel,0,0);
	wmove(nivel,2, 6);
	wprintw(nivel, "NIVEL: %d", *num_ast);
	wrefresh(nivel);
	sleep(3);
}

void subirNivel(Asteroide* asteroides, int* num_ast)
{
	if(*num_ast < MAX_AST)
	{
		asteroides[*num_ast].x = IZQUIERDA;
		asteroides[*num_ast].y = (rand()%(BAJO-ALTO+1)) + ALTO;
		asteroides[*num_ast].tipo = 1;
		(*num_ast)++;

		mostrarNivel(num_ast);
	}
}

WINDOW* mostrargameOver(void)
{
	WINDOW* gameOver = newwin(5,21,12,50);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
	return gameOver;
}

void mostrarVidaExtra(void)
{
	WINDOW* vidaExtra = newwin(5,21,12,50);
	refresh();
	box(vidaExtra,0,0);
	mvwprintw(vidaExtra, 2, 4, "VIDA EXTRA +1");
	wrefresh(vidaExtra);
	sleep(1);
	wclear(vidaExtra);
	wrefresh(vidaExtra);
	delwin(vidaExtra);
}

void pintarNaveChoque(WINDOW* ventana, Nave* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "\"\"\"\"");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "\"\"");
}

void nuevaVidaExtra(VidaExtra* vidasExtra, int* num_vidasExtra)
{
	if(*num_vidasExtra < MAX_EXTRA)
	{
		vidasExtra[*num_vidasExtra].x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
		vidasExtra[*num_vidasExtra].y = (rand()%(BAJO-ALTO+1)) + ALTO;
		(*num_vidasExtra)++;
	}
}

void pintarVidasExtra(WINDOW* ventana, VidaExtra* vidasExtra, int* num_vidasExtra)
{
	for(int i=0; i<*num_vidasExtra; i++)
	{
		mvwprintw(ventana, vidasExtra[i].y, vidasExtra[i].x, "X");
	}
}

void nuevoAsteroideVertical(Asteroide* asteroide)
{
	asteroide->x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
	asteroide->y = ALTO-3;
}

void nuevoAsteroideHorizontal(Asteroide* asteroide)
{
	asteroide->y = (rand()%(BAJO-ALTO+1)) + ALTO;
	asteroide->x = IZQUIERDA-2;
}

void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->y++;

	if(asteroide->y == BAJO+2)
	{
		nuevoAsteroideVertical(asteroide);
	}
}

void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->x++;

	if(asteroide->x == DERECHA+2)
	{
		nuevoAsteroideHorizontal(asteroide);
	}
}

int choqueAsteroide(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	if((asteroide->x >= nave->x) && (asteroide->x <= nave->x+3) && (asteroide->y >= nave->y-1) && (asteroide->y <= nave->y))
	{
		nave->vidas--;
		if(asteroide->tipo == 0)
		{
			nuevoAsteroideVertical(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontal(asteroide);
		}
		return 1;
	}
	else
		return 0;
}

int choqueVidasExtra(WINDOW* ventana, Nave* nave, VidaExtra* vidasExtra, int* num_vidasExtra)
{
	for(int i=0; i<*num_vidasExtra; i++)
	{
		if((vidasExtra[i].x >= nave->x) && (vidasExtra[i].x <= nave->x+3) && (vidasExtra[i].y >= nave->y-1) && (vidasExtra[i].y <= nave->y))
		{
			nave->vidas++;
			vidasExtra[i].x = -1;
			vidasExtra[i].y = -1;
			return 1;
		}
	}
	return 0;
}

void pintarVidas(Nave* nave)
{
	move(2,64); printw("%i",nave->vidas);
	refresh();
}

void actualizar(WINDOW* ventana, Nave* nave)
{
	werase(ventana);
	pintarVidas(nave);
   	box(ventana, 0,0);
}

void pintarNave(WINDOW* ventana, Nave* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "****");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "**");
}

int menuSalida(void)
{
	mciSendString("pause song.mp3", NULL, 0, NULL);
	WINDOW* salida = newwin(5,100,24,9);
    refresh();
    box(salida,0,0);
    keypad(salida, TRUE);

    char** opciones = malloc(2 * sizeof(char*));
    for(int i=0; i<2; i++)
    {
    	opciones[i] = malloc(MAX_LENGHT * sizeof(char));
    }
    opciones[0] = "Jugar otra vez";
    opciones[1] = "Menu";

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
    if(seleccion == 0)
    {
    	werase(salida);
    	wrefresh(salida);
    	return 0;
    }
    else
    {
    	wclear(salida);
    	wrefresh(salida);
    	delwin(salida);
    	return 1;
    }
}

WINDOW* mostrarInfo(void)
{
	WINDOW* info = newwin(8,70,9,28);
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides (O) no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las fleclas");;
	mvwprintw(info,3,1,"Hay 15 niveles distintos");
	mvwprintw(info,4,1,"Existen vidas Extras (X)");
	mvwprintw(info,6,1,"El juego esta a punto de empezar...");
	wrefresh(info);
	return info;
}

WINDOW* mostrarJuego(void)
{
	WINDOW* ventana = newwin(BAJO+2, DERECHA+6, 3, 9);
    refresh();
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    wbkgd(ventana, COLOR_PAIR(1));
    return ventana;
}

void liberarMemoria(Nave* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra, WINDOW* ventana, WINDOW* gameOver)
{
	mciSendString("stop song.mp3", NULL, 0, NULL);
    mciSendString("close song.mp3", NULL, 0, NULL);
    free(nave);
    nave = NULL;
    free(asteroides);
    asteroides = NULL;
    free(num_ast);
    num_ast = NULL;
    free(vidasExtra);
    vidasExtra = NULL;
    free(num_vidasExtra);
    num_vidasExtra = NULL;
    wclear(ventana);
    wrefresh(ventana);
    delwin(ventana);
    wclear(gameOver);
    wrefresh(gameOver);
    delwin(gameOver);
    clear();
    refresh();
}

void inicializarParametros(Nave* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra)
{
	nave->x = 50;
	nave->y = 19;
	nave->vidas = 3;

	asteroides[0].x = 25;
	asteroides[0].y = ALTO;
	asteroides[0].tipo = 0;

	*num_ast = 1;

	vidasExtra[0].x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
	vidasExtra[0].y = (rand()%(BAJO-ALTO+1)) + ALTO;

	*num_vidasExtra = 1;
}

void pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<*num_ast; i++)
    {
    	if(asteroides[i].tipo == 0)
    		pintarAsteroideVertical(ventana, &asteroides[i]);
    	else
    		pintarAsteroideHorizontal(ventana, &asteroides[i]);
    }
}

void jugarSupervivencia (void)
{
    initscr();
	curs_set(0);
	
	WINDOW* info = mostrarInfo();

	mciSendString("play song.mp3 repeat", NULL, 0, NULL);

	wclear(info);
	wrefresh(info);
	delwin(info);

	move(1,3);
	printw("Bienvenido: MODO SUPERVIVENCIA");
	move(2,57); 
	printw("Vidas: ");

	WINDOW* gameOver;
	WINDOW* ventana = mostrarJuego();

    Nave* nave = malloc(sizeof(Nave));
    Asteroide* asteroides = malloc(MAX_AST * sizeof(Asteroide));
    VidaExtra* vidasExtra = malloc(MAX_EXTRA * sizeof(VidaExtra));

    int* num_ast = malloc(sizeof(int));
    int* num_vidasExtra = malloc(sizeof(int));
    float segundos = 0;
    
    int choque_asteroide = 0;
    int choque_vidaExtra = 0;
    int tecla;

    while(1)
    {
    	mciSendString("play song.mp3 repeat", NULL, 0, NULL);

    	inicializarParametros(nave, asteroides, num_ast, vidasExtra, num_vidasExtra);

   		mostrarNivel(num_ast);

	    while(1)
	    {
	        actualizar(ventana, nave);
	        if(segundos > 15)
	        {
	        	subirNivel(asteroides, num_ast);
	        	if(*num_ast == 5 || *num_ast == 8 || *num_ast == 10 || *num_ast == 13) nuevaVidaExtra(vidasExtra, num_vidasExtra);
	        	segundos = 0;
	        }

	        if(choqueVidasExtra(ventana, nave, vidasExtra, num_vidasExtra)) choque_vidaExtra = 1;
	        pintarVidasExtra(ventana, vidasExtra, num_vidasExtra);

	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choqueAsteroide(ventana, nave, &asteroides[i]))
	        	{
	        		choque_asteroide = 1;
	        		break;	
	        	}
	        }

	        pintarAsteroides(ventana, asteroides, num_ast);

	        if(!choque_asteroide)
	        	pintarNave(ventana, nave);
	        else
				pintarNaveChoque(ventana, nave);
	        						
	        wrefresh(ventana);

	        if(choque_asteroide) 
	        {
	        	Beep(500,800);
	        	Sleep(100);
			}
			if(choque_vidaExtra) mostrarVidaExtra();

	        if(nave->vidas == 0)
	        {
	        	choque_asteroide = 0;
	        	gameOver = mostrargameOver();
	        	break;
	        }	

	        tecla = wgetch(ventana);

	        switch(tecla)
	        {
	            case KEY_UP:

	            	if(nave->y>ALTO)
	                	nave->y-=2;
	                break;

	            case KEY_DOWN:

	            	if(nave->y<BAJO)
	                	nave->y+=2;
	                break;

	            case KEY_RIGHT:

	            	if(nave->x<DERECHA)
	                	nave->x+=2;
	                break;

	            case KEY_LEFT:

	            	if(nave->x>IZQUIERDA)
	                	nave->x-=2;
	                break;

	            default:
	            	break;
	        }
	        Sleep(35);
	        segundos +=0.035;
	        choque_asteroide = 0;
	        choque_vidaExtra = 0;
	    }
	    actualizar(ventana,nave);
	    if(menuSalida())
    		break;
    	segundos = 0;
    	for(int i=1; i<*num_ast; i++)
    	{
    		asteroides[i].x = 0;
    		asteroides[i].y = 0;
    		asteroides[i].tipo = 0;
    	}
    	*num_ast = 1;
    }
    liberarMemoria(nave, asteroides, num_ast, vidasExtra, num_vidasExtra, ventana, gameOver);
	endwin();
}