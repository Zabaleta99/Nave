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
} NaveC;

typedef struct 
{
	int x;
	int y;
} AsteroideC;

typedef struct 
{
	int x;
	int y;
}Bala;

void jugarClasico();
void subirNivelClasico(AsteroideC* asteroides, int* num_ast);
void gameOver(WINDOW* gameOver);
void puntuacionFinal (WINDOW* puntuacion, float tiempo, float disparos);
void pintarNaveChoqueClasico(WINDOW* ventana, NaveC* nave);
int choque(WINDOW* ventana, NaveC* nave, AsteroideC* asteroide);
void pintarAsteroideVerticalClasico(WINDOW* ventana, AsteroideC* asteroide);
void actualizarClasico(WINDOW* ventana);
void pintarNaveClasico(WINDOW* ventana, NaveC* nave);
int menuSalidaClasico(void);
void borrarVidas();
void pintarVidasClasico(NaveC* nave);
void actualizarDisparosAcertados (int disparosAcertados, int* numeroDeBala);
void infoClasico (WINDOW* info);
void crearVentanaClasico (WINDOW* ventana);
void pintarBala(WINDOW* ventana, Bala* bala);
int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, AsteroideC* asteroide);
void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala);
void crearBala (Bala* balas, NaveC* nave, int* numBala);
void liberarMemoriaClasico(NaveC* nave, AsteroideC* asteroides, AsteroideC* asteroide1, Bala* balas, int* num_bala, int* num_ast, WINDOW* ventana, WINDOW* gameOver, WINDOW* puntuacionn);

#endif