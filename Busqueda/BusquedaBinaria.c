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

    if ((AutorOriginal=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    Orden=Quicksort(Fichas, ORDEN_POR_AUTOR);

    //Código del alumno del Algoritmo de Búsqueda Binaria

    // Inicializamos los límites de búsqueda
    paredIzq = 0;
    paredDer = Estadisticas.NumeroFichas - 1; // Número total de nodos -1 por el nodo raíz

    strToLowercase(AutorBuscado, AutorOriginal);

    while(paredIzq <= paredDer){
        // Calculamos el indice del elemento central
        centro = paredIzq + (paredDer - paredIzq) / 2;

        strToLowercase(ApellidoTemporal, Orden[centro]->ApellAutor);

        // Comparamos el apellido temporal con el autor buscado
        if((comparacion = strcmp(ApellidoTemporal, AutorBuscado))== 0){
            // Si coincide, guardamos el indice y marcamos como encontrado
            indiceEncontrado = centro;
            Encontrado = true;
            break;
        }
        // Si el autor observado es menor al que queremos encontrar, buscamos por las mitades mirando los apellidos
        else if (comparacion < 0)
            // Si el apellido es menor, buscamos en la mitad derecha
            paredIzq = centro + 1;
        else
            // Si el apellido es mayor, buscamos en la mitad izquierda
            paredDer = centro - 1;
    }

    // Si encontramos al menos un libro del autor, miramos para encontrar todos
    if(Encontrado){
        // "Cerramos" las paredes al indice que hemos encontrado
        paredIzq = indiceEncontrado;
        paredDer = indiceEncontrado;

        // Expandimos hacia la izquierda para encontrar todos los libros del mismo autor
        while (paredIzq > 0) {
            strToLowercase(ApellidoTemporal, Orden[paredIzq - 1]->ApellAutor);
            if (strcmp(AutorBuscado, ApellidoTemporal) != 0) break;
            paredIzq--;
        }

        // Expandimos hacia la derecha para encontrar todos los libros del mismo autor
        while (paredDer < Estadisticas.NumeroFichas - 1) {
            strToLowercase(ApellidoTemporal, Orden[paredDer + 1]->ApellAutor);
            if (strcmp(AutorBuscado, ApellidoTemporal) != 0) break;
            paredDer++;
        }

        Hallados = paredDer - paredIzq + 1;

        // Reservamos memoria para guardar los libros encontrados
        Resultado = (DISCO**)malloc(sizeof(DISCO*)*Hallados);

        // Copiamos los punteros a los libros encontrados al array de resultados
        for(i = 0; i < Hallados; i++){
            Resultado[i] = Orden[paredIzq + i];
        }
    }

    free(Orden);

    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBusquedaBinaria=DifTiempo(inicio,fin);

    // Si no encontramos ningún libro, mostramos un error y salimos
    if (Encontrado == false) {
        VentanaError("No hay autores que cumplan el criterio");
        return;
    }

    // Mostramos los resultados en la pantalla de "Fichas"
    Listado1(Resultado,Hallados,Fichas);
    free(Resultado);
    return;
}