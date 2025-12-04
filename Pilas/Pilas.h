#ifndef NPILAS
    #define NPILAS
    
//Definiciones comunes
#include "..\Comun\Comun.h"

//Definiciones de Pilas

typedef NODO PILA;

//Protipos de TAD PILA
PILA *CrearPila();
PILA *Apilar(PILA *, void *);
PILA *Desapilar(PILA *, void **);
void *ConsultarCima(PILA *);
bool EsPilaVacia(PILA *);

#endif