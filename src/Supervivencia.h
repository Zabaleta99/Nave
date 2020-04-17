#ifndef _SUPERVIVENCIA_H_
#define _SUPERVIVENCIA_H_

#include <curses.h>
#include "Comun.h"


typedef struct 
{
	int x;
	int y;
	int vidas;
} NaveSupervivencia;

typedef struct
{
	int x;
	int y;
} VidaExtra;

void mostrarNivel(int* num_ast);
void subirNivelS(Asteroide* asteroides, int* num_ast);
WINDOW* mostrargameOverS(void);
void mostrarVidaExtra(void);
void pintarNaveChoqueS(WINDOW* ventana, NaveSupervivencia* nave);
void nuevaVidaExtra(VidaExtra* vidasExtra, int* num_vidasExtra);
void pintarVidasExtra(WINDOW* ventana, VidaExtra* vidasExtra, int* num_vidasExtra);
void nuevoAsteroideVerticalS(Asteroide* asteroide);
void nuevoAsteroideHorizontalS(Asteroide* asteroide);
void pintarAsteroideVerticalS(WINDOW* ventana, Asteroide* asteroide);
void pintarAsteroideHorizontalS(WINDOW* ventana, Asteroide* asteroide);
int choqueAsteroide(WINDOW* ventana, NaveSupervivencia* nave, Asteroide* asteroide);
int choqueVidasExtra(WINDOW* ventana, NaveSupervivencia* nave, VidaExtra* vidasExtra, int* num_vidasExtra);
void pintarVidasS(NaveSupervivencia* nave);
void actualizarS(WINDOW* ventana, NaveSupervivencia* nave);
void pintarNaveS(WINDOW* ventana, NaveSupervivencia* nave);
int menuSalidaS(void);
WINDOW* mostrarInfoS(void);
WINDOW* mostrarJuegoS(void);
void liberarMemoriaS(NaveSupervivencia* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra, WINDOW* ventana, WINDOW* gameOver);
void inicializarParametrosS(NaveSupervivencia* nave, Asteroide* asteroides, int* num_ast, VidaExtra* vidasExtra, int* num_vidasExtra);
void pintarAsteroidesS(WINDOW* ventana, Asteroide* asteroides, int* num_ast);
void movimientosJugadorS(int tecla, NaveSupervivencia* nave);
void reestablecerValoresS(int segundos, Asteroide* asteroides, int* num_ast, int choque_asteroide, int choque_vidaExtra);
void jugarSupervivencia(void);

#endif