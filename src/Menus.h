#ifndef SRC_MENUS_H_
#define SRC_MENUS_H_
#include "Usuarios.h"

void menuMain();
int menuInicio ();
void menuRegistrarse(Usuario *usuarios, int size);
Usuario * menuIniciarSesion(Usuario *usuarios, int size);
int menuPlayer (Usuario *player);

#endif