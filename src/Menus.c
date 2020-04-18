#define MAX 15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menus.h"
#include "Usuarios.h"
#include "Supervivencia.h"
#include "Clasico.h"
#include <curses.h>
#include <windows.h>
static int contadorSalida = 0;

void menuMain()
{
    FILE *file = fopen("Usuarios.txt", "r");
    if (file == NULL)
    {
        printf("Error al abrir el fichero Usuarios.txt\n");
        fflush(stdout);
        exit(-1);
    }
    int *size = malloc(sizeof(int));

    Usuario * arrayUsers;
    arrayUsers = leerUsuarios(file, size);

    /*for (int i=0; i<*size; i++)
    {
        printf("Nombre: %s   Contra: %s\n", (arrayUsers+i)->nickname, (arrayUsers+i)->contrasenya);
        fflush(stdout);
    }
    printf(":::::::::::::::::::::::::::::\n");
    fflush(stdout);
    Sleep(6000);*/

    int opcion = menuInicio();
    Usuario *user;

    if (opcion == 0)
    {
        user = menuIniciarSesion(arrayUsers, *size);
        int selected = menuPlayer(user);
        int auxSalir = 0;

        while (auxSalir != 1)
        {

            if (selected == 0)
            {
                jugarSupervivencia();
                selected = menuPlayer(user);
            }
            else if (selected == 1)
            {
                jugarClasico();
                selected = menuPlayer(user);
            }
            else if (selected == 2)
            {

            }
            else if (selected == 3)
            {
                
            }

            else if (selected == 4)
            {
                auxSalir = 1;
                menuMain();
            }
        }
    }

    else if (opcion == 1)
    {
        menuRegistrarse(arrayUsers, *size);
    }

    else
    {
        exit(0);
    }
}

int menuInicio ()
{
	initscr();
	curs_set(0);
	WINDOW* inicio = newwin(5,100,10,9);
    move(9, 42);
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
    werase(inicio);
    erase();
    refresh();
    wrefresh(inicio);
   
    return seleccion;
}

Usuario * menuIniciarSesion(Usuario *usuarios, int size)
{
    move(9, 51);
    attron(A_REVERSE);
    printw("  LOGIN  ");
    attroff(A_REVERSE);
    WINDOW* inicioSesion = newwin(4,100,10,9);
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

    echo(); //ya esta por defecto ensi

    char aux[MAX];
    curs_set(1);
    wmove(inicioSesion, 1, 11);
    wgetnstr(inicioSesion, aux, MAX);
    //fgets(aux, MAX, stdin);
    //fflush(stdin);
    char *userIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", userIntroduced);

    wmove(inicioSesion, 2, 11);
    wgetnstr(inicioSesion, aux, MAX);
    //fgets(aux, MAX, stdin);
    //fflush(stdin);
    char *passIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
    sscanf(aux, "%s", passIntroduced);

    int boolean = 0;
    
    for (int i=0; i<size; i++)
    {
        if ((strcmp(usuarios[i].nickname, userIntroduced) == 0))
        {
            boolean = -1;
            if ((strcmp(usuarios[i].contrasenya, passIntroduced) == 0))
            {
                boolean = 1;
                break;
            }
        }
    }


    if (boolean == 1)
    {
        curs_set(1);
        Usuario *player = (Usuario *) malloc(sizeof(Usuario));
        player->nickname = userIntroduced;
        player->contrasenya = passIntroduced;
        return player;
    }

    if (contadorSalida == 2)
    {
        start_color();
        init_pair(2, COLOR_WHITE, COLOR_BLUE);
        wattron(stdscr, COLOR_PAIR(2));
        move(16, 9);
        wprintw(stdscr, "YOU HAVE ENTERED WRONGLY 3 TIMES. TRY NEXT TIME...");
        wattroff(stdscr, COLOR_PAIR(2));
        refresh();
        Sleep(1500);
        return 0;
    }

    if(boolean == -1)
    {
        move(14, 9);
        wprintw(stdscr, "INCORRECT PASSWORD! TRY AGAIN");
        contadorSalida++;
        menuIniciarSesion(usuarios, size);
        
    }

    if (boolean == 0)
    {
        move(14, 9);
        wprintw(stdscr, "INCORRECT NICKNAME! TRY AGAIN");
        contadorSalida++;
        menuIniciarSesion(usuarios, size);
        
        
    }
}

void menuRegistrarse (Usuario *usuarios, int size)
{
    Usuario *usuariosActualizados;

    move(9, 51);
    attron(A_REVERSE);
    printw("    REGISTRATE    ");
    attroff(A_REVERSE);
    
    WINDOW* registro = newwin(5,100,10,9);
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
        move(15, 9);
        wprintw(stdscr, "THAT NICKNAME ALREADY EXISTS! TRY AGAIN");
        refresh();
        wmove(registro, 1, 11);
        wprintw(registro, "             ");
        wmove(registro, 1, 11);
        wgetnstr(registro, aux, MAX);
        char *userIntroduced = (char *) malloc((strlen(aux)+1) * sizeof(char));
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

    move(15, 9);
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
        move(15, 9);
        wprintw(stdscr, "PASSWORDS ARE DIFFERENT! TRY AGAIN");
        menuRegistrarse(usuarios, size);
    }

    else
    {
        move(15, 9);
        wprintw(stdscr, "REGISTRADO!");
        refresh();

        /*for (int i=0; i<size; i++)
        {
            printf("Na: %s    Ca: %s\n", usuarios[i].nickname, usuarios[i].contrasenya);
            fflush(stdout);
        }
        printf("-----------------------");
        fflush(stdout);*/

        usuariosActualizados = (Usuario *) malloc ((size+1) * sizeof(Usuario));
        for (int i=0; i<size; i++)
        {
            usuariosActualizados[i] = usuarios[i];
            //usuariosActualizados[i].contrasenya = usuarios[i].contrasenya;
            /*free(usuarios[i].nickname);
            free(usuarios[i].contrasenya);*/
        }


       // free(usuarios);

        usuariosActualizados[size].nickname = (char *) malloc((strlen(userIntroduced)+1) * sizeof(char));
        sscanf(userIntroduced, "%s", usuariosActualizados[size].nickname);

        usuariosActualizados[size].contrasenya = (char *) malloc((strlen(passIntroduced)+1) * sizeof(char));
        sscanf(passIntroduced, "%s", usuariosActualizados[size].contrasenya);

        
        size++;

        /*for (int i=0; i<size; i++)
        {
            printf("N: %s    C: %s\n", usuariosActualizados[i].nickname, usuariosActualizados[i].contrasenya);
            fflush(stdout);
        }*/

        escribirUsuarios(usuariosActualizados, size);
        Sleep(1500);
        werase(registro);
        erase();
        wrefresh(registro);
        refresh();

        menuMain();
    }
}

int menuPlayer (Usuario *usuario)
{
    curs_set(0);
    WINDOW* player = newwin(8,100,10,9);
    move(9, 42);
    start_color();
    init_pair(3, COLOR_WHITE, COLOR_RED);
    attron(COLOR_PAIR(3));
    printw("    BIENVENIDO %s    ", usuario->nickname);
    attroff(COLOR_PAIR(3));
    
    refresh();
    box(player,0,0);
    keypad(player, TRUE);

    char** opciones = malloc(5 * sizeof(char*));
    for(int i=0; i<5; i++)
    {
        opciones[i] = malloc(MAX * sizeof(char));
    }
    opciones[0] = "JUGAR SUPERVIVENCIA";
    opciones[1] = "JUGAR CLASICO";
    opciones[2] = "RANKING CLASICO";
    opciones[3] = "MI CUENTA";
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
    werase(player);
    erase();
    refresh();
    wrefresh(player);

    return seleccion;
}


