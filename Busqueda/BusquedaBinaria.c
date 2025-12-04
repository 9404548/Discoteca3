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

void BusquedaBinaria(DISCO *Fichas)
{
    char *Autor;
    DISCO **Resultado=NULL;
    DISCO **Orden=NULL;
    int Hallados=0;
    struct timeval inicio, fin;
    bool Encontrado;

    // Añadir aquí la definición del resto de variables usadas

    if ((Autor=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    Orden=Quicksort(Fichas, ORDEN_POR_AUTOR);

    //Código del alumno del Algoritmo de Búsqueda Binaria

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