#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include "Clasico.h"
#define ALTO 3
#define IZQUIERDA 2
#define BAJO 23
#define DERECHA 95
#define MAX_AST 5
#define MAX_LENGHT 15
#define MAX_BALAS 50


void subirNivelClasico(AsteroideC* asteroides, int* num_ast)
{
	if(*num_ast <= MAX_AST)
	{
		asteroides[*num_ast].x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
		asteroides[*num_ast].y = ALTO;
		(*num_ast)++;
	}
}

void crearBala (Bala* balas, NaveC* nave, int* numBala)
{
	if (*numBala < MAX_BALAS)
	{
		balas[*numBala].x = (nave->x+2);
		balas[*numBala].y = (nave->y-2);
		(*numBala)++;
	}
}

void gameOver(WINDOW* gameOverr)
{
	refresh();
	box(gameOverr,0,0);
	wmove(gameOverr,2, 6);
	wprintw(gameOverr, "GAME OVER");
	wrefresh(gameOverr);
}

void puntuacionFinal (WINDOW* puntuacion, float tiempo, float disparos)
{
	refresh();
	box(puntuacion,0,0);
	wmove(puntuacion,1,2);
	wprintw(puntuacion, "Duracion: %0.2f",tiempo);
	wmove(puntuacion,2,2);
	wprintw(puntuacion,"Puntos por Duracion: %0.2f * 10 = %0.2f",tiempo, tiempo*10);
	wmove(puntuacion,3,2);
	wprintw(puntuacion, "Puntos por Disparos: %0.0f",disparos);
	wmove(puntuacion,4,2);
	wprintw(puntuacion,"----------------------------------");
	wmove(puntuacion,5,2);
	wprintw(puntuacion,"TOTAL: %0.2f", tiempo*10 + disparos);

	wrefresh(puntuacion);
}

void pintarNaveChoqueClasico(WINDOW* ventana, NaveC* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "\"\"\"\"");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "\"\"");
	wrefresh(ventana);

}

void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala)
{
	wmove(ventana, bala->y, bala->x); wprintw(ventana, "#");
	wmove(ventana, bala->y+1, bala->x); wprintw(ventana, "#");
	wmove(ventana, bala->y-1, bala->x); wprintw(ventana, "#");
	bala->x = -1;
	bala->y = -1;
	wrefresh(ventana);
}

int choque(WINDOW* ventana, NaveC* nave, AsteroideC* asteroide)
{
	if((asteroide->x >= nave->x) && (asteroide->x <= nave->x+4) && (asteroide->y >= nave->y-1) && (asteroide->y <= nave->y))
	{
		asteroide->x = -1;
		asteroide->y = -1;
		pintarNaveChoqueClasico(ventana, nave);
		return 1;
	}
	else
		return 0;
}

int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, AsteroideC* asteroide)
{
	if((bala->x == asteroide->x) && ((bala->y == asteroide->y+1) || (bala->y == asteroide->y)))
	{
		asteroide->x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
		asteroide->y = ALTO;
		pintarChoqueAsteroideBala(ventana, bala);
		return 1;
	}
	else
	
		return 0;
}

void pintarAsteroideVerticalClasico(WINDOW* ventana, AsteroideC* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->y++;

	if(asteroide->y == BAJO)
	{
		asteroide->x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
		asteroide->y = ALTO;
	}
}

void pintarBala(WINDOW* ventana, Bala* bala)
{
	wmove(ventana, bala->y, bala->x);
	if (bala->x != -1)
		wprintw(ventana, "^");

	bala->y--;

	if (bala->y == ALTO-2)
	{
		bala->x = -1;
		bala->y = -1;
	}
}

void actualizarClasico(WINDOW* ventana)
{
	werase(ventana);
    box(ventana, 0,0);
}

void pintarNaveClasico(WINDOW* ventana, NaveC* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "*****");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "***");
}

int menuSalidaClasico(void)
{
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
    werase(salida);
    wrefresh(salida);
    if(seleccion == 0)
    	return 0;
    return 1;
}

void borrarVidas()
{
	move(2,38); printw("    ");
	move(2,53); printw("      ");
	refresh();
}

void pintarVidasClasico(NaveC* nave)
{
	move(2,38); printw("%i",nave->vidas);
	 
	for(int i=0; i<nave->corazones;i++)
	{
		move(2,53+i);
		printw("O");
	}
	refresh();
}

void actualizarDisparosAcertados (int disparosAcertados, int* numeroDeBala)
{
	move(2, 65);
	printw("Disparos Acertados: %d", disparosAcertados);
	
	move(2, 95);
	printw("Restantes: %d", (MAX_BALAS-*numeroDeBala));
	refresh();
}

void infoClasico (WINDOW* info)
{
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las flechas, y para diparar el espacio.");;
	mvwprintw(info,3,1,"Tu puntuacion dependera de la duracion de la partida y de los");
	mvwprintw(info,4,1,"asteroides abatidos. Buena suerte!");
	mvwprintw(info,5,1,"El juego esta a punto de empezar...");
	wrefresh(info);
}

void crearVentanaClasico (WINDOW* ventana)
{
	refresh();

    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));
}

void liberarMemoriaClasico(NaveC* nave, AsteroideC* asteroides, AsteroideC* asteroide1, Bala* balas, int* num_bala, int* num_ast, WINDOW* ventana, WINDOW* gameOver, WINDOW* puntuacionn)
{
	mciSendString("stop song.mp3", NULL, 0, NULL);
    mciSendString("close song.mp3", NULL, 0, NULL);
    free(nave);
    nave = NULL;
    free(asteroides);
    asteroides = NULL;
	free(asteroide1);
    asteroide1 = NULL;
    free(num_ast);
    num_ast = NULL;
    free(balas);
    balas = NULL;
    free(num_bala);
    num_bala = NULL;

    erase();
    refresh();
    werase(ventana);
    werase(gameOver);
    werase(puntuacionn);
    wrefresh(gameOver);
    wrefresh(puntuacionn);
    wrefresh(ventana);
}

void jugarClasico (void)
{
    initscr();
	curs_set(0);

	WINDOW* info = newwin(8,70,9,28);
	infoClasico(info);

	mciSendString("play song.mp3 repeat", NULL, 0, NULL);

	werase(info);
	wrefresh(info);

	move(1,3);
	printw("Bienvenido: MODO CLASICO");	    
	move(2,30); 
	printw("Vidas: ");
	move(2,45); 
	printw("Salud: ");

    WINDOW* ventana = newwin(BAJO+2, DERECHA+6, 3, 9);
    crearVentanaClasico (ventana);
    WINDOW* gameOverr = newwin(5,21,5,50);
    WINDOW* puntuacionn = newwin(8,45,12,35);


	NaveC* nave = malloc(sizeof(NaveC));
    nave->x = 50;
    nave->y = 19;
    nave->corazones = 3;
    nave->vidas = 3;

	AsteroideC* asteroides = malloc(MAX_AST * sizeof(AsteroideC));

    int* num_ast = malloc(sizeof(int));
    *num_ast = 1;
    float segundos = 0;
    float tiempo = 0;
    int disparosAcertados = 0;

    AsteroideC* asteroide1 = malloc(sizeof(AsteroideC));
    asteroides[0].x = 25;
    asteroides[0].y = ALTO;

    Bala* balas = malloc(MAX_BALAS * sizeof(Bala));
    
    balas[0].x = -1;
    balas[0].y = -1;
    
    int* numeroDeBala = malloc(sizeof(int));
    *numeroDeBala = 0;
    int contadorBala = 0;
    while(1)
    {
	    pintarVidasClasico(nave);

	    while(1)
	    {
	        actualizarClasico(ventana);

	   		actualizarDisparosAcertados(disparosAcertados, numeroDeBala);

	        if(segundos > 15)
	        {
	        	subirNivelClasico(asteroides, num_ast);
	        	tiempo += segundos;
	        	segundos = 0;
	        }

	        for (int i=0; i<*num_ast; i++)
	        {
	        	for (int j=0; j<*numeroDeBala; j++)
	        	{
					if(choqueBalaAsteroide(ventana, &balas[j], &asteroides[i]))
	        		{
	        			disparosAcertados++;
	        		}

	        	}
	        	
	        }

	        int aux = 0;
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		pintarNaveChoqueClasico(ventana, nave);
	        		Beep(500,800);
	        		Sleep(80);
	        		aux = 1;
	        		break;	
	        	}
	        }

	        if(aux == 1)
	        {
	        	nave->corazones --;

	        	if(nave->corazones == 0)
	        	{
	        		nave->vidas --;
	        		nave->corazones = 3;
	        	}
	        	borrarVidas();
	        	pintarVidasClasico(nave);
	        	if(nave->vidas == 0)
	        	{
	        		gameOver(gameOverr);
	        		puntuacionFinal(puntuacionn, tiempo,disparosAcertados);
	        		break;
	        	}
	        	
	        }

	        for (int i=0; i<*numeroDeBala; i++)
	        {
	        	pintarBala(ventana, &balas[i]);
	        }
	       	

	        for(int i=0; i<*num_ast; i++)
	        {
	        	
	        	pintarAsteroideVerticalClasico(ventana, &asteroides[i]);
	        }
	        
	        pintarNaveClasico(ventana, nave);
	        wrefresh(ventana);

	        int tecla = wgetch(ventana);

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

	            	if(nave->x<DERECHA-1)
	                	nave->x+=2;
	                break;

	            case KEY_LEFT:

	            	if(nave->x>IZQUIERDA)
	                	nave->x-=2;
	                break;

	            case 32:
	            	crearBala(balas, nave, numeroDeBala);
	                break;

	            default:
	            	break;
	        }
	        Sleep(45);
	        segundos +=0.035;
	    }

	    if(menuSalidaClasico() == 1)
    		break;
    }
    
    liberarMemoriaClasico(nave, asteroides, asteroide1, balas, numeroDeBala, num_ast, ventana, gameOverr, puntuacionn);

	endwin();
}