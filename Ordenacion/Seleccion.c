/*****************************************
 * Nombre: Seleccion
 * Argumentos: LIBRO *Ficha:       Array de las fichas de libros
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de libros en un doble puntero a las fichas de Libros,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Selección.
 * Reglas de uso:
 * Código de Retorno: LIBRO **: Doble puntero ordenado por el criterio pedido a las fichas de libros.
 * Programador: Rodrigo-dFL (Dec 25)
 *****************************************/

#include "../Discoteca.h"

DISCO **Seleccion(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;

    // Añade aquí la definición del resto de variables necesarias
    int i, j, min_indx;
    DISCO *tmp;
    char Autor1[100], Autor2[100];

    gettimeofday(&inicio, NULL);
    Orden = InitOrden(Ficha);

    // Código del Alumno del Algoritmo de ordenación por Selección
    for (i = 0; i < Estadisticas.NumeroFichas - 1; i++)
    {
        min_indx = i;
        // Encontrar el elemento mínimo en la parte no ordenada
        for (j = i + 1; j < Estadisticas.NumeroFichas; j++)
        {
            int comparador = 0;
            // Si se ordena por autor, ponemos el campo como "Apellido, Nombre"
            if (Campo == ORDEN_POR_AUTOR)
            {
                strcpy(Autor1, Orden[j]->ApellAutor);
                if (Orden[j]->NomAutor != NULL)
                {
                    strcat(Autor1, ", ");
                    strcat(Autor1, Orden[j]->NomAutor);
                }
                strcpy(Autor2, Orden[min_indx]->ApellAutor);
                if (Orden[min_indx]->NomAutor != NULL)
                {
                    strcat(Autor2, ", ");
                    strcat(Autor2, Orden[min_indx]->NomAutor);
                }
                // Comparamos los nombres de los autores
                comparador = strcmp(Autor1, Autor2);
                /***********************************************************************
                 * Si Autor1 es igual que Autor2 -> comparador = 0                     *
                 * Si Autor1 es lexicográficamente menor que Autor2 -> comparador < 0  *
                 * Si Autor1 es lexicográficamente mayor que Autor2 -> comparador > 0  *
                 **********************************************************************/
            }
            else
            {
                // Si se ordena por título, no hace falta hacer cambios
                comparador = strcmp(Orden[j]->Obra, Orden[min_indx]->Obra);
            }

            // Si Orden[j] es menor que Orden[min_indx], actualizar min_indx a j
            if (comparador < 0)
            {
                min_indx = j;
            }
        }

        // Si se encontró un nuevo mínimo (i es distinto de min_indx), actualizamos Orden[i]
        if (min_indx != i)
        {
            tmp = Orden[i];
            Orden[i] = Orden[min_indx];
            Orden[min_indx] = tmp;
        }
    }

    gettimeofday(&fin, NULL);
    Estadisticas.TiempoSeleccion = DifTiempo(inicio, fin);

    return (Orden);
}