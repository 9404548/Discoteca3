#ifndef NORDENACION
    #define NORDENACION

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Ventanas\Ventanas.h"

//Prototipos de funciones de Ordenacion
DISCO **Seleccion(DISCO *, int);
DISCO **Burbuja(DISCO *, int);
DISCO **Insercion(DISCO *, int);
DISCO **Quicksort(DISCO *, int);
DISCO **InitOrden(DISCO *);

#endif