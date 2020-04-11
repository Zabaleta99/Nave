#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#define ALTO 2
#define IZQUIERDA 1
#define BAJO 19
#define DERECHA 95
#define MAX_AST 10
#define MAX_LENGHT 15

typedef struct 
{
	int x;
	int y;
} Nave;

typedef struct 
{
	int x;
	int y;
} Asteroide;

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
	if(*num_ast <= MAX_AST)
	{
		asteroides[*num_ast].x = IZQUIERDA;
		asteroides[*num_ast].y = (rand()%(BAJO-ALTO+1)) + ALTO;
		(*num_ast)++;

		mostrarNivel(num_ast);
	}
}

void gameOver(void)
{
	WINDOW* gameOver = newwin(5,21,12,50);
	refresh();
	box(gameOver,0,0);
	wmove(gameOver,2, 6);
	wprintw(gameOver, "GAME OVER");
	wrefresh(gameOver);
}

void pintarNaveChoque(WINDOW* ventana, Nave* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "\"\"\"\"");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "\"\"");
	wrefresh(ventana);
}

int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
{
	if((asteroide->x >= nave->x) && (asteroide->x <= nave->x+3) && (asteroide->y >= nave->y-1) && (asteroide->y <= nave->y))
	{
		pintarNaveChoque(ventana, nave);
		gameOver();
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

void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide)
{
	wmove(ventana, asteroide->y, asteroide->x); wprintw(ventana, "O");

	asteroide->x++;

	if(asteroide->x == DERECHA)
	{
		asteroide->y = (rand()%(BAJO-ALTO+1)) + ALTO;
		asteroide->x = IZQUIERDA;
	}
}

void actualizar(WINDOW* ventana)
{
	werase(ventana);
    box(ventana, 0,0);
}

void pintarNave(WINDOW* ventana, Nave* nave)
{
	wmove(ventana, nave->y, nave->x); wprintw(ventana, "****");
	wmove(ventana, nave->y-1, nave->x+1); wprintw(ventana, "**");
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

int main(void)
{
    initscr();
	curs_set(0);
	move(1,3);
	printw("Bienvenido: MODO SUPERVIVENCIA");
    WINDOW* ventana = newwin(BAJO+2, DERECHA+5, 3, 9);

    refresh();

    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));

    while(1)
    {
	    Nave* nave = malloc(sizeof(Nave));
	    nave->x = 50;
	    nave->y = 19;

	    Asteroide* asteroides = malloc(MAX_AST * sizeof(Asteroide));

	    int* num_ast = malloc(sizeof(int));
	    *num_ast = 1;
	    float segundos = 0;

	    Asteroide* asteroide1 = malloc(sizeof(Asteroide));
	    asteroides[0].x = 25;
	    asteroides[0].y = ALTO;

	    mostrarNivel(num_ast);
	    
	    while(1)
	    {
	    	
	        actualizar(ventana);
	        if(segundos > 15)
	        {
	        	subirNivel(asteroides, num_ast);
	        	segundos = 0;
	        }

	        int aux = 0;
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		aux = 1;
	        		break;	
	        	}
	        }

	        if(aux == 1)
	        {
	        	break;
	        }

	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(i==0)
	        	{
	        		pintarAsteroideVertical(ventana, &asteroides[i]);
	        	}
	        	else
	        	{
	        		pintarAsteroideHorizontal(ventana, &asteroides[i]);
	        	}
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
	    }

	    if(menuSalida() == 1)
    		break;
    }
    
	endwin();

    return 0;
}