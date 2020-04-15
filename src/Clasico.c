#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#define ALTO 3
#define IZQUIERDA 2
#define BAJO 19
#define DERECHA 95
#define MAX_AST 5
#define MAX_LENGHT 15
#define MAX_BALAS 100

typedef struct 
{
	int x;
	int y;
	int vidas;
	int corazones;
} Nave;

typedef struct 
{
	int x;
	int y;
} Asteroide;

typedef struct 
{
	int x;
	int y;
}Bala;

void subirNivel(Asteroide* asteroides, int* num_ast)
{
	if(*num_ast <= MAX_AST)
	{
		asteroides[*num_ast].x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
		asteroides[*num_ast].y = ALTO;
		(*num_ast)++;
	}
}

void crearBala (Bala* balas, Nave* nave, int* numBala)
{
	if (*numBala <= MAX_BALAS)
	{
		balas[*numBala].x = (nave->x+2);
		balas[*numBala].y = (nave->y-2);
		(*numBala)++;
	}
}

void gameOver(void)
{
	WINDOW* gameOver = newwin(5,21,5,50);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
}

void puntuacion (float tiempo, float disparos)
{
	WINDOW* puntuacion = newwin(8,45,12,35);
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

void pintarNaveChoque(WINDOW* ventana, Nave* nave)
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

int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	if((asteroide->x >= nave->x) && (asteroide->x <= nave->x+4) && (asteroide->y >= nave->y-1) && (asteroide->y <= nave->y))
	{
		asteroide->x = -1;
		asteroide->y = -1;
		pintarNaveChoque(ventana, nave);
		return 1;
	}
	else
		return 0;
}

int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide)
{
	if((bala->x == asteroide->x) && ((bala->y == asteroide->y+1) || (bala->y == asteroide->y)))
	{
		asteroide->x = -1;
		asteroide->y = -1;
		pintarChoqueAsteroideBala(ventana, bala);
		return 1;
	}
	else
	
		return 0;
}

void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide)
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

void actualizar(WINDOW* ventana)
{
	werase(ventana);
    box(ventana, 0,0);
}

void pintarNave(WINDOW* ventana, Nave* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "*****");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "***");
}

int menuSalida(void)
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
	move(2,57); printw("    ");
	move(2,71); printw("      ");
	refresh();
}

void pintarVidas(Nave* nave)
{
	move(2,57); printw("%i",nave->vidas);
	 
	for(int i=0; i<nave->corazones;i++)
	{
		move(2,71+i);
		printw("O");
	}
	refresh();
}

int main(void)
{
    initscr();
	curs_set(0);

	WINDOW* info = newwin(8,70,9,28);
	refresh();
	box(info,0,0);
	mvwprintw(info,1,1,"El juego consiste en que los asteroides no choquen con la nave.");
	mvwprintw(info,2,1,"Para mover la nave usa las flechas, y para diparar el espacio.");;
	mvwprintw(info,3,1,"Tu puntuacion dependera de la duracion de la partida y de los");
	mvwprintw(info,4,1,"asteroides abatidos. Buena suerte!");
	mvwprintw(info,5,1,"El juego esta a punto de empezar...");
	wrefresh(info);

	mciSendString("play song.mp3 repeat", NULL, 0, NULL);

	werase(info);
	wrefresh(info);

	move(1,3);
	printw("Bienvenido: MODO CLASICO");	    
	move(2,50); 
	printw("Vidas: ");
	move(2,65); 
	printw("Salud: ");
    WINDOW* ventana = newwin(BAJO+2, DERECHA+6, 3, 9);

    refresh();

    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));

    while(1)
    {
	    Nave* nave = malloc(sizeof(Nave));
	    nave->x = 50;
	    nave->y = 19;
	    nave->corazones = 3;
	    nave->vidas = 3;

	    pintarVidas(nave);

	    Asteroide* asteroides = malloc(MAX_AST * sizeof(Asteroide));

	    int* num_ast = malloc(sizeof(int));
	    *num_ast = 1;
	    float segundos = 0;
	    float tiempo = 0;
	    float disparosAcertados = 0;

	    Asteroide* asteroide1 = malloc(sizeof(Asteroide));
	    asteroides[0].x = 25;
	    asteroides[0].y = ALTO;

	    Bala* balas = malloc(MAX_BALAS * sizeof(Bala));
	    
	    balas[0].x = -1;
	    balas[0].y = -1;
	    
	    int* numeroDeBala = malloc(sizeof(int));
	    *numeroDeBala = 1;
	    int contadorBala = 0;

	    while(1)
	    {
	    	
	        actualizar(ventana);
	        if(segundos > 15)
	        {
	        	subirNivel(asteroides, num_ast);
	        	tiempo += segundos;
	        	segundos = 0;
	        }

	        //for para comprobar choques bala asteroide
	        for (int i=0; i<*numeroDeBala; i++)
	        {
	        	if(choqueBalaAsteroide(ventana, &balas[*numeroDeBala-1], &asteroides[i]))
	        	{
	        		disparosAcertados++;
	        	}
	        }

	        int aux = 0;
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		pintarNaveChoque(ventana, nave);
	        		Beep(500,800);
	        		Sleep(500);
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
	        	pintarVidas(nave);
	        	if(nave->vidas == 0)
	        	{
	        		gameOver();
	        		puntuacion(tiempo,disparosAcertados);
	        		break;
	        	}
	        	
	        }

	        pintarBala(ventana, &balas[(*numeroDeBala)-1]);

	        for(int i=0; i<*num_ast; i++)
	        {
	        	
	        	pintarAsteroideVertical(ventana, &asteroides[i]);
	        }
	        
	        pintarNave(ventana, nave);
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
	        Sleep(60);
	        segundos +=0.060;
	    }

	    if(menuSalida() == 1)
    		break;
    }
    
	endwin();

    return 0;
}