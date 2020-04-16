#ifndef _OPERACIONES_H_
#define _OPERACIONES_H_

#include <curses.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include "Clasico.h"

#define ALTO 3
#define IZQUIERDA 2
#define BAJO 23
#define DERECHA 95
#define MAX_AST 10
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

WINDOW* mostrarInfo(void);

WINDOW* mostrarJuego(void);

WINDOW* mostrarGameOver(void);

WINDOW* mostrarPuntuacion (float tiempo, int* disparosAcertados);

void subirNivel(Asteroide* asteroides, int* num_ast);

void crearBala (Bala* balas, Nave* nave, int* num_balas);

void pintarNaveChoque(WINDOW* ventana, Nave* nave);

void pintarChoqueAsteroideBala (WINDOW* ventana, Bala* bala);

void pintarNuevoAsteroide(Asteroide* asteroide);

int choque(WINDOW* ventana, Nave* nave, Asteroide* asteroide);

int choqueBalaAsteroide(WINDOW* ventana, Bala* bala, Asteroide* asteroide, int* disparosAcertados);

void pintarAsteroideVertical(WINDOW* ventana, Asteroide* asteroide);

void pintarBala(WINDOW* ventana, Bala* bala);

void pintarNave(WINDOW* ventana, Nave* nave);

int menuSalida(void);

void pintarVidas(Nave* nave);

void actualizarDisparosAcertados (int* disparosAcertados, int* num_balas);

void actualizar(WINDOW* ventana, Nave* nave, int* disparosAcertados, int* num_balas);

void inicializarParametros(Nave* nave, Asteroide* asteroides, int* num_ast, int* num_balas, int* disparosAcertados);

void liberarMemoria(Nave* nave, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados, WINDOW* ventana, WINDOW* gameOver, WINDOW* puntuacion);

void reestablecerValores(int segundos, int tiempo, Asteroide* asteroides, int* num_ast, Bala* balas, int* num_balas, int* disparosAcertados);

void movimientosJugador(int tecla, Nave* nave, Bala* balas, int* num_balas);

void jugarClasico(void);

#endif