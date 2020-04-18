#ifndef SRC_MENUS_H_
#define SRC_MENUS_H_
#include "Usuarios.h"
#include <curses.h>

void menuMain();
int menuInicio ();
void menuRegistrarse(Usuario *usuarios, int size);
Usuario * menuIniciarSesion(Usuario *usuarios, int size);
int menuPlayer (Usuario *player);

void liberarMemoriaMenuInicio(char ** opciones, WINDOW* ventana);
void liberarMemoriaMenuMain (int *size, Usuario* user, Usuario* arrayUsers);
void liberarMemoriaMenuInicioSesion(char* userIntroduced, char* passIntroduced, WINDOW* inicioSesion);
void liberarMemoriaMenuRegistrarse(WINDOW* registro, Usuario* usuariosActualizados, int size, char* userIntroduced, char* passIntroduced, char* passConfiIntroduced);
void liberarMemoriaMenuPlayer(WINDOW* player, char** opciones);

#endif