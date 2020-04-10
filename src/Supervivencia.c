#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

#define ALTO 2
#define IZQUIERDA 1
#define BAJO 19
#define DERECHA 95

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

int main(void)
{
    initscr();
	curs_set(0);
	move(1,3);
	printw("Bienvenido: MODO SUPERVIVENCIA");
    WINDOW* ventana = newwin(BAJO+2, DERECHA+5, 4, 9);

    refresh();

    keypad(ventana, TRUE);
    nodelay(ventana, TRUE);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    wbkgd(ventana, COLOR_PAIR(1));

    Nave* nave = malloc(sizeof(Nave));
    nave->x = 50;
    nave->y = 19;

    Asteroide* asteroide1 = malloc(sizeof(Asteroide));
    asteroide1->x = 25;
    asteroide1->y = ALTO;

    Asteroide* asteroide2 = malloc(sizeof(Asteroide));
    asteroide2->x = 75;
    asteroide2->y = ALTO;

    Asteroide* asteroide_horizontal1 = malloc(sizeof(Asteroide));
    asteroide_horizontal1->x = IZQUIERDA;
    asteroide_horizontal1->y = 15;

    Asteroide* asteroide_horizontal2 = malloc(sizeof(Asteroide));
    asteroide_horizontal2->x = IZQUIERDA;
    asteroide_horizontal2->y = 5;
    
     while(1)
    {
    	
        actualizar(ventana);
        if(choque(ventana, nave, asteroide1) == 1|| choque(ventana, nave, asteroide2) || choque(ventana, nave, asteroide_horizontal1) || choque(ventana, nave, asteroide_horizontal2))
        {
        	break;
        }
        pintarAsteroideVertical(ventana, asteroide1);
        pintarAsteroideVertical(ventana, asteroide2);
        pintarAsteroideHorizontal(ventana, asteroide_horizontal1);
        pintarAsteroideHorizontal(ventana, asteroide_horizontal2);
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

      	if(tecla == 10)
        	break;

        Sleep(35);

    }

    move(26, 9);
    curs_set(1);
    printw("Pulsa cualquier tecla para continuar...");
    while(!getch());
        
	endwin();

    return 0;
}