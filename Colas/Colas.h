#ifndef NCOLAS
    #define NCOLAS

//Definiciones comunes
#include "..\Comun\Comun.h"

//Definiciones de Colas
typedef struct _Cola {
    NODO *Cabecera;
    NODO *Final;
} COLA;

//Protipos del TAD Cola
COLA *CrearCola();
int Encolar(COLA *, void *);
void *Desencolar (COLA *);
void *ConsultarCola(COLA *);
int InsertarCabecera(COLA *, void *);
bool EsColaVacia(COLA *);

#endif