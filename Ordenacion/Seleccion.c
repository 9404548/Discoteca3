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

// Función auxiliar para comparar dos discos según el campo especificado
static int comparar(DISCO *a, DISCO *b, int Campo)
{
    if (Campo == ORDEN_POR_AUTOR) {
        char Autor1[256], Autor2[256];
        strcpy(Autor1, a->ApellAutor);
        if (a->NomAutor != NULL) {
            strcat(Autor1, ", ");
            strcat(Autor1, a->NomAutor);
        }
        strcpy(Autor2, b->ApellAutor);
        if (b->NomAutor != NULL) {
            strcat(Autor2, ", ");
            strcat(Autor2, b->NomAutor);
        }
        return strcmp(Autor1, Autor2);
    } else {
        return strcmp(a->Obra, b->Obra);
    }
}

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