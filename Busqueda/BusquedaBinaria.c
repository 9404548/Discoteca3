/*****************************************
 * Nombre: BusquedaBinaria
 * Argumentos: LIBRO *Fichas:       Array de las fichas de libros
 * Descripción: Después de capturar los apellidos de un autor, busca las fichas de libros de ese autor,
 *              por el método de búsqueda binaria
 *              La comparación de los apellidos se hace en mayúsculas. 
 *              Después se muestran los resultados en una pantalla de scroll.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Busqueda.h"

void strToLowercase(char *destino, char *origen){
    int i = 0;

    while(origen[i]){
        if(origen[i] >= 'A' && origen[i] <= 'Z') destino[i] = origen[i] + 32;
        else destino[i] = origen[i];
        i++;
    }
    
    destino[i] = '\0';

    return;
}

void BusquedaBinaria(DISCO *Fichas)
{
    char AutorBuscado[256];
    char *AutorOriginal;
    DISCO **Resultado=NULL;
    DISCO **Orden=NULL;
    int Hallados=0;
    struct timeval inicio, fin;
    bool Encontrado;
    int comparacion = 0;
    char ApellidoTemporal[256];
    int i, j, paredIzq, paredDer, centro, indiceEncontrado;
    DISCO *pAux;

    // Añadir aquí la definición del resto de variables usadas

    if ((AutorOriginal=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    Orden=Quicksort(Fichas, ORDEN_POR_AUTOR);

    //Código del alumno del Algoritmo de Búsqueda Binaria

    paredIzq = 0;
    paredDer = Estadisticas.NumeroFichas - 1;
    
    strToLowercase(AutorBuscado, AutorOriginal);

    while(paredIzq <= paredDer){
        centro = paredIzq + (paredDer - paredIzq) / 2;

        strToLowercase(ApellidoTemporal, Orden[centro]->ApellAutor);

        if((comparacion = strcmp(ApellidoTemporal, AutorBuscado))== 0){
            indiceEncontrado = centro;
            Encontrado = true; 
            break;
        } 
        else if (comparacion < 0) // El autor observado actualmente es menor al autor a encontrar
            paredIzq = centro + 1;
        else
            paredDer = centro - 1;
    }
    
    if(Encontrado){
        paredIzq = indiceEncontrado;
        paredDer = indiceEncontrado;

        while (paredIzq > 0) {
            strToLowercase(ApellidoTemporal, Orden[paredIzq - 1]->ApellAutor);
            if (strcmp(AutorBuscado, ApellidoTemporal) != 0) break;
            paredIzq--;
        }

        while (paredDer < Estadisticas.NumeroFichas - 1) {
            strToLowercase(ApellidoTemporal, Orden[paredDer + 1]->ApellAutor);
            if (strcmp(AutorBuscado, ApellidoTemporal) != 0) break;
            paredDer++;
        }

        Hallados = paredDer - paredIzq + 1;

        Resultado = (DISCO**)malloc(sizeof(DISCO*)*Hallados);

        for(i = 0; i < Hallados; i++){
            Resultado[i] = Orden[paredIzq + i];
        }
    }
    

    free(Orden);
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBusquedaBinaria=DifTiempo(inicio,fin);

    if (Encontrado == false) {
        VentanaError("No hay autores que cumplan el criterio");
        return;
    }
    
    Listado1(Resultado,Hallados,Fichas);
    free(Resultado);
    return;
    
}