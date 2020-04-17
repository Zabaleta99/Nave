#ifndef _CLASICO_H_
#define _CLASICO_H_

#include <curses.h>
#include "Comun.h"

typedef struct 
{
	int x;
	int y;
	int vidas;
	int corazones;
} NaveClasico;

typedef struct 
{
	int x;
	int y;
}Bala;

WINDOW* mostrarInfoC(void);
WINDOW* mostrarJuegoC(void);
WINDOW* mostrarGameOverC(void);
WINDOW* mostrarPuntuacion (float tiempo, int* disparosAcertados);
void subirNivelC(Asteroide* asteroides, int* num_ast);
void crearBala (Bala* balas, NaveClasico* nave, int* num_balas);
void pintarNaveChoqueC(WINDOW* ventana, NaveClasico* nave);
void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala);
void pintarAsteroidesC(WINDOW* ventana, Asteroide* asteroides, int* num_ast);
void nuevoAsteroideVerticalC(Asteroide* asteroide);
void nuevoAsteroideHorizontalC(Asteroide* asteroide);
int choqueC(WINDOW* ventana, NaveClasico* nave, Asteroide* asteroide);
int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide, int* disparosAcertados);
void pintarAsteroideVerticalC(WINDOW* ventana, Asteroide* asteroide);
void pintarBala(WINDOW* ventana, Bala* bala);
void pintarNaveC(WINDOW* ventana, NaveClasico* nave);
int menuSalidaC(void);
void pintarVidasC(NaveClasico* nave);
void actualizarDisparosAcertados (int* disparosAcertados, int* num_balas);
void actualizarC(WINDOW* ventana, NaveClasico* nave, int* disparosAcertados, int* num_balas);
void inicializarParametrosC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados);
void liberarMemoriaC(NaveClasico* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, WINDOW* ventana, WINDOW* gameOver, WINDOW* puntuacion);
void reestablecerValoresC(int segundos, int tiempo, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, int choqueAsteroide, int choqueBala);
void movimientosJugadorC(int tecla, NaveClasico* nave, Bala* balas, int* num_balas);
void jugarClasico(void);

#endif