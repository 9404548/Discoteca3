#ifndef NLISTAS
    #define NLISTAS
    
//Definiciones comunes
#include "..\Comun\Comun.h"

//Definiciones de Listas
typedef struct _Lista { /* Definimos el tipo lista con un puntero */
    NODO *Primero;
    NODO *Ultimo;
} LISTA;

//Prototipos del TAD Lista
LISTA *CrearLista();
int InsertarListaDerecha(LISTA *, void *);
int InsertarListaIzquierda(LISTA *, void *);
void *BorrarListaDerecha(LISTA *);
void *BorrarListaIzquierda(LISTA *);
void *ConsultarListaDerecha(LISTA *);
void *ConsultarListaIzquierda(LISTA *);
bool EsListaVacia(LISTA *);
int LongitudLista(LISTA *);

#endif