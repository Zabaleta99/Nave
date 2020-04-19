#define MAX 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menus.h"
#include "Usuarios.h"
#include "Supervivencia.h"
#include "Rankings.h"
#include "Clasico.h" 
#include <curses.h>
#include <windows.h>
static int MAX_X;
static int MAX_Y;
static int contadorSalida = 0;


void liberarMemoriaMenuMain (int *size, Usuario* arrayUsers)
{
    for (int i=0; i<*size; i++)
    {
        free(arrayUsers[i].nickname);
        arrayUsers[i].nickname = NULL;
        free(arrayUsers[i].contrasenya);
        arrayUsers[i].contrasenya = NULL;
        free(arrayUsers[i].puntuaciones);
        arrayUsers[i].puntuaciones = NULL;
    }
    free(arrayUsers);
    arrayUsers = NULL;

    free(size);
    size = NULL;
}

void liberarMemoriaMenuInicio(char** opciones, WINDOW* inicio)
{
    for (int i=0; i<3; i++)
    {
        free(opciones[i]);
        opciones[i] = NULL;
    }
    free (opciones);
    opciones = NULL;

    werase(inicio);
    erase();
    refresh();
    wrefresh(inicio);
}   

void liberarMemoriaMenuInicioSesion(char* userIntroduced, char* passIntroduced, WINDOW* inicioSesion)
{
    free(userIntroduced);
    userIntroduced = NULL;

    free(passIntroduced);
    passIntroduced = NULL;

    werase(inicioSesion);
    erase();
    refresh();
    wrefresh(inicioSesion);
}

void liberarMemoriaMenuRegistrarse(WINDOW* registro, Usuario* usuariosActualizados, int size, char* userIntroduced, char* passIntroduced, char* passConfiIntroduced)
{
    werase(registro);
    erase();
    wrefresh(registro);
    refresh();

    for (int i=0; i<size; i++)
    {
        free(usuariosActualizados[i].nickname);
        usuariosActualizados[i].nickname = NULL;
        free(usuariosActualizados[i].contrasenya);
        usuariosActualizados[i].contrasenya = NULL;
    }
    free(usuariosActualizados);
    usuariosActualizados = NULL;

    free(userIntroduced);
    userIntroduced = NULL;

    free(passIntroduced);
    passIntroduced = NULL;

    free(passConfiIntroduced);
    passConfiIntroduced = NULL;
}

void liberarMemoriaMenuPlayer(WINDOW* player, char** opciones)
{
    for (int i=0; i<4; i++)
    {
        free(opciones[i]);
        opciones[i] = NULL;
    }
    free (opciones);
    opciones = NULL;

    werase(player);
    erase();
    refresh();
    wrefresh(player);

}

int menuInicio(void)
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, MAX_Y, MAX_X);
    WINDOW* inicio = newwin(5,MAX_X/2,(MAX_Y/2)-2.5, MAX_X/4);
    move((MAX_Y/2)-3.5, MAX_X/4+1);
    start_color();
    init_pair(3, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(3));
    printw("    BIENVENIDO A MULTIJUEGOS    ");
    attroff(COLOR_PAIR(3));
    
    refresh();
    box(inicio,0,0);
    keypad(inicio, TRUE);

    char** opciones = malloc(3 * sizeof(char*));
    for(int i=0; i<3; i++)
    {
        opciones[i] = malloc(MAX * sizeof(char));
    }
    opciones[0] = "INICIAR SESION";
    opciones[1] = "REGISTRARSE";
    opciones[2] = "CERRAR JUEGO";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
        for(int i=0; i<3; i++)
        {
            if(i==seleccion)
                wattron(inicio, A_REVERSE);
            mvwprintw(inicio, i+1, 1, "%s", opciones[i]);
            wattroff(inicio, A_REVERSE);
        }
        wrefresh(inicio);

        eleccion = wgetch(inicio);

        switch(eleccion)
        {
            case KEY_UP:
                seleccion--;
                if(seleccion == -1)
                    seleccion = 0;
                break;
            case KEY_DOWN:
                seleccion++;
                if(seleccion == 3)
                    seleccion = 2;
                break;
            default:
                break;
        }
        if(eleccion == 10)
            break;
    }

    liberarMemoriaMenuInicio(opciones, inicio);
   
    return seleccion;
}

int menuIniciarSesion(Usuario *usuarios, int size)
{
    echo();
    move((MAX_Y/2)-3, MAX_X/4+1);
    attron(A_REVERSE);
    printw("  LOGIN  ");
    attroff(A_REVERSE);
    WINDOW* inicioSesion = newwin(4,MAX_X/2,(MAX_Y/2)-2, MAX_X/4);
    refresh();
    box(inicioSesion,0,0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);

    wmove(inicioSesion, 1,1);
    wattron(inicioSesion, COLOR_PAIR(1));
    wprintw(inicioSesion, "NICKNAME:");

    wmove(inicioSesion, 2,1);
    wprintw(inicioSesion, "PASSWORD:");

    wattroff(inicioSesion, COLOR_PAIR(1));
    wrefresh(inicioSesion);

    char aux[MAX];
    curs_set(1);
    wmove(inicioSesion, 1, 11);
    wgetnstr(inicioSesion, aux, MAX);

    char *userIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", userIntroduced);

    wmove(inicioSesion, 2, 11);
    wgetnstr(inicioSesion, aux, MAX);

    char *passIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", passIntroduced);

    int boolean = 0;
    int player;
    
    for (int i=0; i<size; i++)
    {
        if ((strcmp(usuarios[i].nickname, userIntroduced) == 0))
        {
            boolean = -1;
            if ((strcmp(usuarios[i].contrasenya, passIntroduced) == 0))
            {
                boolean = 1;
                player = i;
                break;
            }
        }
    }

    if (boolean == 1)
    {
        curs_set(1);
        liberarMemoriaMenuInicioSesion(userIntroduced, passIntroduced, inicioSesion);
        return player;
    }

    if (contadorSalida == 2)
    {
        start_color();
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
        wattron(stdscr, COLOR_PAIR(2));
        move((MAX_Y/2)+4, MAX_X/4);
        wprintw(stdscr, "YOU HAVE ENTERED WRONGLY 3 TIMES. TRY NEXT TIME...");
        wattroff(stdscr, COLOR_PAIR(2));
        refresh();

        Sleep(1000);

        liberarMemoriaMenuInicioSesion(userIntroduced, passIntroduced, inicioSesion);

        exit(0);
    }

    if(boolean == -1)
    {
        move((MAX_Y/2)+3, MAX_X/4);
        printw("INCORRECT PASSWORD! TRY AGAIN");
        contadorSalida++;
        menuIniciarSesion(usuarios, size);
    }

    if (boolean == 0)
    {
        move((MAX_Y/2)+3, MAX_X/4);
        wprintw(stdscr, "INCORRECT NICKNAME! TRY AGAIN");
        contadorSalida++;
        menuIniciarSesion(usuarios, size); 
    }
}

void menuRegistrarse (Usuario *usuarios, int size)
{
    Usuario *usuariosActualizados;
    echo();
    move((MAX_Y/2)-3.5, MAX_X/4+1);
    attron(A_REVERSE);
    printw("    REGISTRATE    ");
    attroff(A_REVERSE);
    
    WINDOW* registro = newwin(5,MAX_X/2,(MAX_Y/2)-2.5, MAX_X/4);
    refresh();
    box(registro,0,0);
    

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);

    wmove(registro, 1,1);
    wattron(registro, COLOR_PAIR(1));
    wprintw(registro, "NICKNAME:");

    wmove(registro, 2,1);
    wprintw(registro, "PASSWORD:");

    wmove(registro, 3,1);
    wprintw(registro, "CONFIRM PASSWORD:");

    wattroff(registro, COLOR_PAIR(1));
    wrefresh(registro);


    char aux[MAX];
    curs_set(1);
    wmove(registro, 1, 11);

    wgetnstr(registro, aux, MAX);
    char *userIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", userIntroduced);

    int bl = 0;
    for (int i=0; i<size; i++)
    {
        if ((strcmp(usuarios[i].nickname, userIntroduced) == 0))
        {
            bl = 1;
            break;
        }
    }

    while (bl == 1)
    {
        move((MAX_Y/2)+3.5, MAX_X/4);
        wprintw(stdscr, "THAT NICKNAME ALREADY EXISTS! TRY AGAIN");
        refresh();
        wmove(registro, 1, 11);
        wprintw(registro, "             ");
        wmove(registro, 1, 11);

        wgetnstr(registro, aux, MAX);
        userIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
        sscanf(aux, "%s", userIntroduced);

        bl = 0;
        for (int i=0; i<size; i++)
        {
            if ((strcmp(usuarios[i].nickname, userIntroduced) == 0))
            {
                bl = 1;
                break;
            }
        }
    }

    move((MAX_Y/2)+3.5, MAX_X/4);
    wprintw(stdscr, "                                         ");
    refresh();


    wmove(registro, 2, 11);
    wgetnstr(registro, aux, MAX);
    char *passIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", passIntroduced);

    wmove(registro, 3, 19);
    wgetnstr(registro, aux, MAX);
    char *passConfiIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", passConfiIntroduced);

    if (strcmp(passIntroduced, passConfiIntroduced) != 0)
    {
        move((MAX_Y/2)+3.5, MAX_X/4);
        wprintw(stdscr, "PASSWORDS ARE DIFFERENT! TRY AGAIN");
        menuRegistrarse(usuarios, size);
    }

    else
    {
        move((MAX_Y/2)+3.5, MAX_X/4);
        wprintw(stdscr, "REGISTRADO!");
        refresh();

        usuariosActualizados = (Usuario *) malloc ((size+1) * sizeof(Usuario));
        for (int i=0; i<size; i++)
        {
            usuariosActualizados[i] = usuarios[i];
        }

        usuariosActualizados[size].nickname = (char *) malloc((strlen(userIntroduced)+1) * sizeof(char));
        sscanf(userIntroduced, "%s", usuariosActualizados[size].nickname);

        usuariosActualizados[size].contrasenya = (char *) malloc((strlen(passIntroduced)+1) * sizeof(char));
        sscanf(passIntroduced, "%s", usuariosActualizados[size].contrasenya);

        usuariosActualizados[size].puntuaciones = malloc(2 * sizeof(float));
        
        size++;

        escribirUsuarios(usuariosActualizados, size);
        Sleep(1000);

        liberarMemoriaMenuRegistrarse(registro, usuariosActualizados, size, userIntroduced, passIntroduced, passConfiIntroduced);
        menuMain();
    }
}

int menuPlayer(void)
{
    curs_set(0);
    noecho();
    WINDOW* player = newwin(7, MAX_X/2, (MAX_Y/2)-3.5, MAX_X/4);
    move((MAX_Y/2)-4.5, MAX_X/4);
    start_color();
    init_pair(3, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(3));
    printw("    BIENVENIDO    ");
    attroff(COLOR_PAIR(3));
    
    refresh();
    box(player,0,0);
    keypad(player, TRUE);

    char** opciones = malloc(5 * sizeof(char*));
    for(int i=0; i<5; i++)
    {
        opciones[i] = malloc(MAX * sizeof(char));
    }
    opciones[0] = "JUGAR CLASICO";
    opciones[1] = "JUGAR SUPERVIVENCIA";
    opciones[2] = "RANKING CLASICO";
    opciones[3] = "RANKING SUPERVIVENCIA";
    opciones[4] = "SALIR";

    int eleccion;
    int seleccion = 0;

    while(1)
    {
        for(int i=0; i<5; i++)
        {
            if(i==seleccion)
                wattron(player, A_REVERSE);
            mvwprintw(player, i+1, 1, "%s", opciones[i]);
            wattroff(player, A_REVERSE);
        }
        wrefresh(player);

        eleccion = wgetch(player);

        switch(eleccion)
        {
            case KEY_UP:
                seleccion--;
                if(seleccion == -1)
                    seleccion = 0;
                break;
            case KEY_DOWN:
                seleccion++;
                if(seleccion == 5)
                    seleccion = 4;
                break;
            default:
                break;
        }
        if(eleccion == 10)
            break;
    }

    liberarMemoriaMenuPlayer(player, opciones);

    return seleccion;
}

void menuMain()
{
    FILE *file = fopen("Usuarios.txt", "r");
    if (file == NULL)
    {
        printf("Error al abrir el fichero Usuarios.txt\n");
        fflush(stdout);
        exit(-1);
    }
    int* size = malloc(sizeof(int));

    Usuario* usuarios = leerUsuarios(file, size);
    int player;
    int opcion;
    while(1)
    {
        opcion = menuInicio();
        switch(opcion)
        {   case 0:
                player = (int) menuIniciarSesion(usuarios, *size);
                int selected;
                while(1)
                {
                    selected = menuPlayer();
                    switch(selected)
                    {
                        case 0:
                            jugarClasico(usuarios, player);
                            escribirUsuarios(usuarios, *size);
                            break;
                        case 1:
                            jugarSupervivencia(usuarios, player);
                            escribirUsuarios(usuarios, *size);
                            break;
                        case 2:
                            rankingClasico(usuarios, *size);
                            break;
                        case 3:
                            rankingSupervivencia(usuarios, *size);
                            break;
                        default:
                            break;
                    }
                    if(selected == 4) break;
                }
                break;
            case 1:
                menuRegistrarse(usuarios, *size);
                break;
            default:
                break;
        }
        if(opcion == 2) break; 
    }
    liberarMemoriaMenuMain (size, usuarios);
    exit(0);    
}
