#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#define ALTO 2
#define IZQUIERDA 2
#define BAJO 19
#define DERECHA 95
#define MAX_AST 10
#define MAX_LENGHT 15

typedef struct 
{
	int x;
	int y;
	int vidas;
} Nave;

typedef struct 
{
	int x;
	int y;
	int tipo;
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
		asteroides[*num_ast].tipo = 1;
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
	Sleep(500);
}

void nuevoAsteroideVertical(Asteroide* asteroide)
{
	asteroide->x = (rand()%(DERECHA-IZQUIERDA+1)) + IZQUIERDA;
	asteroide->y = ALTO-2;
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

	if(asteroide->y == BAJO)
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

int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide)
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
	move(2,57); 
	printw("Vidas: ");
    WINDOW* ventana = newwin(BAJO+2, DERECHA+6, 3, 9);

    refresh();

    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));

    Nave* nave = malloc(sizeof(Nave));
    Asteroide* asteroides = malloc(MAX_AST * sizeof(Asteroide));

    int* num_ast = malloc(sizeof(int));
    float segundos = 0;
    
    int aux = 0;
    int tecla;

    while(1)
    {
    	nave->x = 50;
    	nave->y = 19;
    	nave->vidas = 3;

    	asteroides[0].x = 25;
   		asteroides[0].y = ALTO;
   		asteroides[0].tipo = 0;

   		*num_ast = 1;

   		mostrarNivel(num_ast);

	    while(1)
	    {
	        actualizar(ventana, nave);
	        if(segundos > 15)
	        {
	        	subirNivel(asteroides, num_ast);
	        	segundos = 0;
	        }
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(choque(ventana, nave, &asteroides[i]))
	        	{
	        		aux = 1;
	        		break;	
	        	}
	        }
	        if(aux == 0)
	        	pintarNave(ventana, nave);
	        else
	        {
	        	aux = 0;
	        	pintarNaveChoque(ventana, nave);
	        }
	        
	        if(nave->vidas == 0)
	        {
	        	gameOver();
	        	break;
	        }
	       
	        for(int i=0; i<*num_ast; i++)
	        {
	        	if(asteroides[i].tipo == 0)
	        		pintarAsteroideVertical(ventana, &asteroides[i]);
	        	else
	        		pintarAsteroideHorizontal(ventana, &asteroides[i]);
	        }							
	        wrefresh(ventana);
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
	endwin();
    return 0;
}