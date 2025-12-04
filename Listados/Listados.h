#ifndef NLISTADOS
    #define NLISTADOS

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Ventanas\Ventanas.h"

//Include de Pilas
#include "..\Pilas\Pilas.h"

//Include de Colas
#include "..\Colas\Colas.h"

//Include de Listas
#include "..\Listas\Listas.h"

//Prototipos de funciones de listado
void Listado1(DISCO **, int, DISCO *);
void Listado2(DISCO **, int, DISCO *);

#endif