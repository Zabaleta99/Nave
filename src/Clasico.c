#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include "Clasico.h"

void crearBalas (Bala* balas, Nave* nave, int* num_balas)
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

WINDOW* mostrarGameOver(void)
{
	WINDOW* gameOver = newwin(5,21,5,50);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
	return gameOver;
}

WINDOW* mostrarPuntuacion (float tiempo, int* disparosAcertados)
{
	WINDOW* puntuacion = newwin(8,45,12,35);
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
	wprintw(puntuacion,"TOTAL: %0.2f", tiempo*10 + *disparosAcertados);

	wrefresh(puntuacion);
	return puntuacion;
}

void pintarNaveChoque(WINDOW* ventana, Nave* nave)
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

void nuevoAsteroideHorizontal(Asteroide* asteroide)
{
	asteroide->x = IZQUIERDA-2;
	asteroide->y = (rand()%(BAJO-ALTO+1)) + ALTO;
}

void nuevoAsteroideVertical(Asteroide* asteroide)
{
	asteroide->x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
	asteroide->y = ALTO-3;
}

int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	if((asteroide->x >= nave->x) && (asteroide->x <= nave->x+3) && (asteroide->y >= nave->y-1) && (asteroide->y <= nave->y))
	{
		nave->corazones--;
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

int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide, int* disparosAcertados)
{
	if((bala->x == asteroide->x) && ((bala->y == asteroide->y+1) || (bala->y == asteroide->y)) || (bala->x+1 == asteroide->x) && ((bala->y == asteroide->y+1) || (bala->y == asteroide->y)))
	{
		if(asteroide->tipo == 0)
		{
			nuevoAsteroideVertical(asteroide);
		}
		else
		{
			nuevoAsteroideHorizontal(asteroide);
		}
		pintarChoqueAsteroideBala(ventana, bala);
		(*disparosAcertados)++;
		return 1;
	}
	else
	
		return 0;
}

void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->x++;

	if(asteroide->x == DERECHA+1)
	{
		nuevoAsteroideHorizontal(asteroide);
	}
}

void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->y++;

	if(asteroide->y == BAJO+1)
	{
		nuevoAsteroideVertical(asteroide);
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
    werase(salida);
    wrefresh(salida);
    if(seleccion == 0)
    	return 0;
    return 1;
}

void pintarVidas(Nave* nave)
{
	move(2,38); printw("%i",nave->vidas);
	
	mvprintw(2,53,"   ");
	for(int i=0; i<nave->corazones;i++)
	{
		mvprintw(2,53+i,"O");
	}
	refresh();
}

void actualizarDisparosAcertados (int* disparosAcertados, int* num_balas)
{
	mvprintw(2, 86, "  ");
	mvprintw(2, 65, "Disparos Acertados: %d", *disparosAcertados);
	
	mvprintw(2, 107, "  ");
	mvprintw(2, 95, "Restantes: %d", (MAX_BALAS-*num_balas));
	refresh();
}

void actualizar(WINDOW* ventana, Nave* nave, int* disparosAcertados, int* num_balas)
{
	pintarVidas(nave);
    actualizarDisparosAcertados(disparosAcertados, num_balas);
	werase(ventana);
	box(ventana, 0,0);
}

void crearAsteroidesHorizontales(Asteroide* asteroides, int* num_ast)
{
	int contador = 0;
	while(contador != 2)
	{
		nuevoAsteroideHorizontal(&asteroides[*num_ast]);
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
		nuevoAsteroideVertical(&asteroides[*num_ast]);
		asteroides[*num_ast].tipo = 0;
		(*num_ast)++;
		contador++;
	}
}

void subirNivel(Asteroide* asteroides, int* num_ast)
{
	crearAsteroidesVerticales(asteroides, num_ast);
	crearAsteroidesHorizontales(asteroides, num_ast);
}

void inicializarParametros(Nave* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados)
{
    nave->x = 50;
    nave->y = 19;
    nave->corazones = 3;
    nave->vidas = 3;

    for(int i=0; i<5; i++)
    {
    	nuevoAsteroideVertical(&asteroides[i]);
    	asteroides[i].tipo = 0;
    }

	*num_ast = 5;
	*num_balas = 0;
	*disparosAcertados = 0;
}

void liberarMemoria(Nave* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, WINDOW* ventana, WINDOW* gameOver, WINDOW* puntuacion)
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
    wclear(gameOver);
    wrefresh(gameOver);
    delwin(gameOver);
    wclear(puntuacion);
    wrefresh(puntuacion);
    delwin(puntuacion);
    clear();
    refresh();
}

WINDOW* mostrarInfo(void)
{
	WINDOW* info = newwin(8,70,9,28);
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

WINDOW* mostrarJuego(void)
{
	WINDOW* ventana = newwin(BAJO+2, DERECHA+6, 3, 9);
    refresh();
    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));
    return ventana;
}

void reestablecerValores(int segundos, int tiempo, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados)
{
	segundos = 0;
	tiempo = 0;
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
	*num_ast = 1;
	*num_balas = 0;
	*disparosAcertados = 0;
}

void movimientosJugador(int tecla, Nave* nave, Bala* balas, int* num_balas)
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

void jugarClasico(void)
{
    initscr();
	curs_set(0);

	WINDOW* info = mostrarInfo();

	mciSendString("play song.mp3 repeat", NULL, 0, NULL);

	wclear(info);
	wrefresh(info);
	delwin(info);

	move(1,3);
	printw("Bienvenido: MODO CLASICO");	    
	move(2,30); 
	printw("Vidas: ");
	move(2,45); 
	printw("Salud: ");

    WINDOW* ventana = mostrarJuego();

    WINDOW* gameOver;
    WINDOW* puntuacion;

    Nave* nave = malloc(sizeof(Nave));
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

	    inicializarParametros(nave, asteroides, num_ast, num_balas, disparosAcertados);

	    while(1)
	    {
	        actualizar(ventana, nave, disparosAcertados, num_balas);

	        if(segundos > 30)
	        {
	        	subirNivel(asteroides, num_ast);
	        	tiempo += segundos;
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
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		choqueAsteroide = 1;
	        		break;	
	        	}
	        }
	        for (int i=0; i<*num_balas; i++)
	        {
	        	pintarBala(ventana, &balas[i]);
	        }

	        pintarAsteroides(ventana, asteroides, num_ast);
	        
	        if(!choqueAsteroide)
	        	pintarNave(ventana, nave);
	        else
	        	pintarNaveChoque(ventana, nave);

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
        		gameOver = mostrarGameOver();
        		puntuacion = mostrarPuntuacion(tiempo,disparosAcertados);
        		choqueAsteroide = 0;
        		choqueBala = 0;
        		break;
        	}

	    	tecla = wgetch(ventana);
	    	movimientosJugador(tecla, nave, balas, num_balas);

	        Sleep(50);
	        segundos +=0.050;
	        choqueAsteroide = 0;
	        choqueBala = 0;
	    }
	    actualizar(ventana, nave, disparosAcertados, num_balas);
	    if(menuSalida())
    		break;
    	reestablecerValores(segundos, tiempo, asteroides, num_ast, balas, num_balas, disparosAcertados);
    }
    liberarMemoria(nave, asteroides, num_ast, balas, num_balas, disparosAcertados, ventana, gameOver, puntuacion);
	endwin();
}