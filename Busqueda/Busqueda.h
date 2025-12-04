#ifndef NBUSQUEDA
    #define NBUSQUEDA

//Definiciones comunes
#include "..\Comun\Comun.h"

//Include de Curses
#include <ncursesw/curses.h>

//Include para dibujar los menus
#include "..\Listados\Listados.h"

//Include para la ordenación
#include "../Ordenacion/Ordenacion.h"

//Estructura del Arbol
typedef struct _arbol {
    void *Raiz;
    char Autor[256];
    struct _arbol *HojaDerecha;
    struct _arbol *HojaIzquierda;
} ARBOL;

//Prototipos de funciones de busqueda
char *LeerAutor();
void BusquedaSecuencial(DISCO *);
void BusquedaBinaria(DISCO *);
void BusquedaArbol(DISCO *);

#endif