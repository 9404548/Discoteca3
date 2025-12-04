/*****************************************
 * Nombre: Seleccion
 * Argumentos: LIBRO *Ficha:       Array de las fichas de libros
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de libros en un doble puntero a las fichas de Libros,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Selección.
 * Reglas de uso: 
 * Código de Retorno: LIBRO **: Doble puntero ordenado por el criterio pedido a las fichas de libros.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

DISCO **Seleccion(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    
    //Añade aquí la definición del resto de variables necesarias

    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);

    //Código del Alumno del Algoritmo de ordenación por Selección

    gettimeofday(&fin,NULL);
    Estadisticas.TiempoSeleccion=DifTiempo(inicio,fin);

    return(Orden);
}