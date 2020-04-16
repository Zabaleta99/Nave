#ifndef SRC_CLASICO_H_
#define SRC_CLASICO_H_

#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

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

void jugarClasico();
void subirNivelClasico(Asteroide* asteroides, int* num_ast);
void gameOver(WINDOW* gameOver);
void puntuacionFinal (WINDOW* puntuacion, float tiempo, float disparos);
void pintarNaveChoqueClasico(WINDOW* ventana, Nave* nave);
int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide);
void pintarAsteroideVerticalClasico(WINDOW* ventana, Asteroide* asteroide);
void actualizarClasico(WINDOW* ventana);
void pintarNaveClasico(WINDOW* ventana, Nave* nave);
int menuSalidaClasico(void);
void borrarVidas();
void pintarVidasClasico(Nave* nave);
void actualizarDisparosAcertados (int disparosAcertados, int* numeroDeBala);
void infoClasico (WINDOW* info);
void crearVentanaClasico (WINDOW* ventana);
void pintarBala(WINDOW* ventana, Bala* bala);
int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide);
void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala);
void crearBala (Bala* balas, Nave* nave, int* numBala);
void liberarMemoriaClasico(Nave* nave, Asteroide* asteroides, Asteroide* asteroide1, Bala* balas, int* num_bala, int* num_ast, WINDOW* ventana, WINDOW* gameOver, WINDOW* puntuacionn);

#endif