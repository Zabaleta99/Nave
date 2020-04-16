#ifndef SRC_SUPERVIVENCIA_H_
#define SRC_SRC_SUPERVIVENCIA_H__H_

#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct
{
	int x;
	int y;
} VidaExtra;

void mostrarNivel(int* num_ast);
void subirNivel(Asteroide* asteroides, int* num_ast);
WINDOW* mostrargameOver(void);
void mostrarVidaExtra(void);
void pintarNaveChoque(WINDOW* ventana, Nave* nave);
void nuevaVidaExtra(VidaExtra* vidasExtra, int* num_vidasExtra);
void pintarVidasExtra(WINDOW* ventana, VidaExtra* vidasExtra, int* num_vidasExtra);
void nuevoAsteroideVertical(Asteroide* asteroide);
void nuevoAsteroideHorizontal(Asteroide* asteroide);
void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide);
void pintarAsteroideHorizontal(WINDOW* ventana, Asteroide* asteroide);
int choqueAsteroide(WINDOW* ventana, Nave* nave, Asteroide* asteroide);
int choqueVidasExtra(WINDOW* ventana, Nave* nave, VidaExtra* vidasExtra, int* num_vidasExtra);
void pintarVidas(Nave* nave);
void actualizar(WINDOW* ventana, Nave* nave);
void pintarNave(WINDOW* ventana, Nave* nave);
int menuSalida(void);
WINDOW* mostrarInfo(void);
WINDOW* mostrarJuego(void);
void liberarMemoria(Nave* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra, WINDOW* ventana, WINDOW* gameOver);
void inicializarParametros(Nave* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra);
void pintarAsteroides(WINDOW* ventana, Asteroide* asteroides, int* num_ast);
void jugarSupervivencia (void);



#endif