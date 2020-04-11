#ifndef SRC_MENUS_H_
#define SRC_MENUS_H_
#include "Usuarios.h"

int menuInicio (void);
void menuRegistrarse(Usuario *usuarios, int size);
Usuario * menuIniciarSesion(Usuario *usuarios, int size);
void menuPlayer (Usuario *player);

#endif