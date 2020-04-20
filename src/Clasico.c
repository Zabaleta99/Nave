#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include "Clasico.h"

static int ALTO = 0;
static int IZQUIERDA = 0;
static int BAJO = 0;
static int DERECHA = 0;

static int alturaTerminal = 0;
static int anchuraTerminal = 0;

#define MAX_AST 20
#define MAX_LENGHT 15
#define MAX_BALAS 200

void crearBalas (Bala* balas, NaveClasico* nave, int* num_balas)
{
	if (*num_balas < MAX_BALAS)
	{
		balas[*num_balas].x = nave->x+1;
		balas[*num_balas].y = nave->y-2;
		balas[*num_balas+1].x = nave->x+2;
		balas[*num_balas+1].y = nave->y-2;
		*num_balas += 2;
	}
}

void mostrarGameOverC(void)
{
	int alturaVentanaClasico = BAJO;
	int anchuraVentanaClasico = DERECHA+6;
	WINDOW* gameOver = newwin(alturaTerminal/6,anchuraTerminal/4,alturaVentanaClasico/4.2, anchuraVentanaClasico/2.3);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
	wclear(gameOver);
	delwin(gameOver);
}

void mostrarPuntuacion (Usuario* usuarios, int player, float tiempo, int* disparosAcertados)
{
	float puntuacionTotal = tiempo*10 + *disparosAcertados;
	if(puntuacionTotal > usuarios[player].puntuaciones[0])
		usuarios[player].puntuaciones[0] = puntuacionTotal;

	int alturaVentanaClasico = BAJO;
	int anchuraVentanaClasico = DERECHA+6;
	WINDOW* puntuacion = newwin(7, 45, alturaTerminal/2-3.5, anchuraTerminal/2-22.5);
	refresh();
	box(puntuacion,0,0);
	wmove(puntuacion,1,2);
	wprintw(puntuacion, "Duracion: %0.2f",tiempo);
	wmove(puntuacion,2,2);
	wprintw(puntuacion,"Puntos por Duracion: %0.2f * 10 = %0.2f",tiempo, tiempo*10);
	wmove(puntuacion,3,2);
	wprintw(puntuacion, "Puntos por Disparos: %d",*disparosAcertados);
	wmove(puntuacion,4,2);
	wprintw(puntuacion,"----------------------------------");
	wmove(puntuacion,5,2);
	wprintw(puntuacion,"TOTAL: %0.2f", puntuacionTotal);
	wrefresh(puntuacion);
	wclear(puntuacion);
	delwin(puntuacion);
}

void pintarNaveChoqueC(WINDOW* ventana, NaveClasico* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "\"\"\"\"");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "\"\"");

}

void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala)
{
	wmove(ventana, bala->y, bala->x); wprintw(ventana, "#");
	bala->x = -1;
	bala->y = -1;
}

void nuevoAsteroideHorizontalC(Asteroide* asteroide)
{
	asteroide->x = IZQUIERDA-2;
	asteroide->y = (rand()%(BAJO-ALTO+1)) + ALTO;
}

void nuevoAsteroideVerticalC(Asteroide* asteroide)
{
	asteroide->x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
	asteroide->y = ALTO-3;
}

int choqueC(WINDOW* ventana, NaveClasico* nave, Asteroide* asteroide)
{
	if((asteroide->x >= nave->x) && (asteroide->x <= nave->x+3) && (asteroide->y >= nave->y-1) && (asteroide->y <= nave->y))
	{
		nave->corazones--;
		if(asteroide->tipo == 0)
		{
			nuevoAsteroideVerticalC(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontalC(asteroide);
		}
		return 1;
	}
	else
		return 0;
}

int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide, int* disparosAcertados)
{
	if((bala->x == asteroide->x) && ((bala->y == asteroide->y+1) || (bala->y == asteroide->y)) || (bala->x+1 == asteroide->x) && ((bala->y == asteroide->y+1) || (bala->y == asteroide->y)))
	{
		if(asteroide->tipo == 0)
		{
			nuevoAsteroideVerticalC(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontalC(asteroide);
		}
		pintarChoqueAsteroideBala(ventana, bala);
		(*disparosAcertados)++;
		return 1;
	}
	else
	
		return 0;
}

void pintarAsteroideHorizontalC(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->x++;

	if(asteroide->x == DERECHA+1)
	{
		nuevoAsteroideHorizontalC(asteroide);
	}
}

void pintarAsteroideVerticalC(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->y++;

	if(asteroide->y == BAJO+1)
	{
		nuevoAsteroideVerticalC(asteroide);
	}
}

void pintarBala(WINDOW* ventana, Bala* bala)
{
	mvwprintw(ventana, bala->y, bala->x, "^");

	bala->y--;

	if (bala->y == ALTO-2)
	{
		bala->x = -1;
		bala->y = -1;
	}
}

void pintarAsteroidesC(WINDOW* ventana, Asteroide* asteroides, int* num_ast)
{
	for(int i=0; i<*num_ast; i++)
    {
    	if(asteroides[i].tipo == 0)
    		pintarAsteroideVerticalC(ventana, &asteroides[i]);
    	else
    		pintarAsteroideHorizontalC(ventana, &asteroides[i]);
    }
}

void pintarNaveC(WINDOW* ventana, NaveClasico* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "****");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "**");
}

int menuSalidaC(void)
{
	mciSendString("pause song.mp3", NULL, 0, NULL);
	WINDOW* salida = newwin(alturaTerminal/5,anchuraTerminal-20,alturaTerminal-(alturaTerminal/5)-1, IZQUIERDA+1);
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

void pintarVidasC(NaveClasico* nave)
{
	move(2,8); printw("%i",nave->vidas);
	
	mvprintw(2,19,"   ");
	for(int i=0; i<nave->corazones;i++)
	{
		mvprintw(2,19+i,"O");
	}
	refresh();
}

void actualizarDisparosAcertados (int* disparosAcertados, int* num_balas)
{
	mvprintw(2, 45, "   ");
	mvprintw(2, 25, "Disparos Acertados: %d", *disparosAcertados);
	
	mvprintw(2, 62, "   ");
	mvprintw(2, 51, "Restantes: %d", (MAX_BALAS-*num_balas));
	refresh();
}

void actualizarC(WINDOW* ventana, NaveClasico* nave, int* disparosAcertados, int* num_balas)
{
	pintarVidasC(nave);
    actualizarDisparosAcertados(disparosAcertados, num_balas);
	werase(ventana);
	box(ventana, 0,0);
}

void crearAsteroidesHorizontales(Asteroide* asteroides, int* num_ast)
{
	int contador = 0;
	while(contador != 2)
	{
		nuevoAsteroideHorizontalC(&asteroides[*num_ast]);
		asteroides[*num_ast].tipo = 1;
		(*num_ast)++;
		contador++;
	}
}

void crearAsteroidesVerticales(Asteroide* asteroides, int* num_ast)
{
	int contador = 0;
	while(contador != 3)
	{
		nuevoAsteroideVerticalC(&asteroides[*num_ast]);
		asteroides[*num_ast].tipo = 0;
		(*num_ast)++;
		contador++;
	}
}

void subirNivelC(Asteroide* asteroides, int* num_ast)
{
	crearAsteroidesVerticales(asteroides, num_ast);
	crearAsteroidesHorizontales(asteroides, num_ast);
}

void inicializarParametrosC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados)
{
    nave->x = (DERECHA+6)/2;
    nave->y = 3*(BAJO+3)/4;
    nave->corazones = 3;
    nave->vidas = 3;

    for(int i=0; i<5; i++)
    {
    	nuevoAsteroideVerticalC(&asteroides[i]);
    	asteroides[i].tipo = 0;
    }

	*num_ast = 5;
	*num_balas = 0;
	*disparosAcertados = 0;
}

void liberarMemoriaC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, WINDOW* ventana)
{
	mciSendString("stop song.mp3", NULL, 0, NULL);
    mciSendString("close song.mp3", NULL, 0, NULL);
    free(nave);
    nave = NULL;
    free(asteroides);
    asteroides = NULL;
    free(num_ast);
    num_ast = NULL;
    free(balas);
    balas = NULL;
    free(num_balas);
    num_balas = NULL;
    free(disparosAcertados);
    disparosAcertados = NULL;
    wclear(ventana);
    wrefresh(ventana);
    delwin(ventana);
    clear();
    refresh();
}

WINDOW* mostrarInfoC(void)
{
	WINDOW* info = newwin(alturaTerminal/4,anchuraTerminal/1.7,alturaTerminal/2.5, anchuraTerminal/4);
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las flechas, y para diparar el espacio.");;
	mvwprintw(info,3,1,"Tu puntuacion dependera de la duracion de la partida y de los");
	mvwprintw(info,4,1,"asteroides abatidos. Buena suerte!");
	mvwprintw(info,5,1,"El juego esta a punto de empezar...");
	wrefresh(info);
	return info;
}

WINDOW* mostrarJuegoC(void)
{
	WINDOW* ventana = newwin(BAJO+3, DERECHA+6, ALTO, IZQUIERDA+1);
    refresh();
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));
    return ventana;
}

void reestablecerValoresC(Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados)
{
	for(int i=0; i<*num_ast; i++)
	{
		asteroides[i].x = 0;
		asteroides[i].y = 0;
	}
	for(int i=0; i<*num_balas; i++)
	{
		balas[i].x = 0;
		balas[i].y = 0;
	}
	*num_ast = 0;
	*num_balas = 0;
	*disparosAcertados = 0;
}

void movimientosJugadorC(int tecla, NaveClasico* nave, Bala* balas, int* num_balas)
{
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
        	crearBalas(balas, nave, num_balas);
            break;

        default:
        	break;
    }
}

void tamanyoAbsolutoC()
{
	getmaxyx(stdscr, alturaTerminal, anchuraTerminal);
	BAJO = (alturaTerminal * 0.83)-3;
	ALTO = alturaTerminal*0.13;
	IZQUIERDA = (anchuraTerminal*0.074)-1;
	DERECHA = (anchuraTerminal * 0.85)-6;
}

void jugarClasico(Usuario* usuarios, int player)
{
    initscr();
	curs_set(0);

	tamanyoAbsolutoC();
	WINDOW* info = mostrarInfoC();

	mciSendString("play song.mp3 repeat", NULL, 0, NULL);

	wclear(info);
	wrefresh(info);
	delwin(info);

	move(1,3);
	printw("Bienvenido: MODO CLASICO");	    
	move(2,1); 
	printw("Vidas: ");
	move(2,12); 
	printw("Salud: ");

    WINDOW* ventana = mostrarJuegoC();

    NaveClasico* nave = malloc(sizeof(NaveClasico));
    Asteroide* asteroides = malloc(MAX_AST * sizeof(Asteroide));
    Bala* balas = malloc(MAX_BALAS * sizeof(Bala));

    int* num_ast = malloc(sizeof(int));
    int* num_balas = malloc(sizeof(int));
    int* disparosAcertados = malloc(sizeof(int));

    float segundos = 0;
    float tiempo = 0;

    int choqueAsteroide = 0;
    int choqueBala = 0;
    int tecla;

    while(1)
    {

	    mciSendString("play song.mp3 repeat", NULL, 0, NULL);

	    inicializarParametrosC(nave, asteroides, num_ast, num_balas, disparosAcertados);

	    while(1)
	    {
	        actualizarC(ventana, nave, disparosAcertados, num_balas);

	        if(segundos > 30)
	        {
	        	subirNivelC(asteroides, num_ast);
	        	segundos = 0;
	        }

	        for (int i=0; i<*num_ast; i++)
	        {
	        	for (int j=0; j<*num_balas; j++)
	        	{
					if(balas[j].x != -1 && choqueBalaAsteroide(ventana, &balas[j], &asteroides[i], disparosAcertados))
	        		{
	        			choqueBala = 1;
	        			break;
	        		}
	        	}	
	        }
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choqueC(ventana, nave, &asteroides[i]))
	        	{
	        		choqueAsteroide = 1;
	        		break;	
	        	}
	        }
	        for (int i=0; i<*num_balas; i++)
	        {
	        	pintarBala(ventana, &balas[i]);
	        }

	        pintarAsteroidesC(ventana, asteroides, num_ast);
	        
	        if(!choqueAsteroide)
	        	pintarNaveC(ventana, nave);
	        else
	        	pintarNaveChoqueC(ventana, nave);

	        wrefresh(ventana);

	        if(choqueAsteroide)
	        {
	        	Beep(500,800);
	        }
	        if(choqueBala)
	        {
	        	Beep(800,50);
	        }

	        if(nave->corazones == 0)
        	{
        		nave->vidas --;
        		nave->corazones = 3;
        	}
        	if(nave->vidas == 0)
        	{
        		mostrarGameOverC();
        		mostrarPuntuacion(usuarios, player, tiempo,disparosAcertados);
        		choqueAsteroide = 0;
	        	choqueBala = 0;
	        	segundos = 0;
	        	tiempo = 0;
        		break;
        	}

	    	tecla = wgetch(ventana);
	    	movimientosJugadorC(tecla, nave, balas, num_balas);

	        Sleep(50);
	        segundos +=0.050;
	        tiempo +=0.050;
	        choqueAsteroide = 0;
	        choqueBala = 0;
	    }
	    actualizarC(ventana, nave, disparosAcertados, num_balas);
	    if(menuSalidaC())
    		break;
    	reestablecerValoresC(asteroides, num_ast, balas, num_balas, disparosAcertados);
    }
    liberarMemoriaC(nave, asteroides, num_ast, balas, num_balas, disparosAcertados, ventana);
	endwin();
}