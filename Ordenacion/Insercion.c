/*****************************************
 * Nombre: Inserción
 * Argumentos: LIBRO *Ficha:       Array de las fichas de libros
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de libros en un doble puntero a las fichas de Libros,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Inserción.
 * Reglas de uso:
 * Código de Retorno: LIBRO **: Doble puntero ordenado por el criterio pedido a las fichas de libros.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

DISCO **Insercion(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    int i, j;
    DISCO *aux;
    char Autor1[100], Autor2[100];

    gettimeofday(&inicio, NULL);
    Orden = InitOrden(Ficha);

    for (i = 1; i < Estadisticas.NumeroFichas; i++)
    {
        // Guardamos la ficha en una variable auxiliar para comparar
        aux = Orden[i];
        j = i - 1;
        // Mientras j sea válido y Orden[j] sea mayor que aux, desplazamos los elementos
        while (j >= 0)
        {
            int comparador;
            if (Campo == ORDEN_POR_AUTOR)
            {
                // Ponemos los autores como "Apellido, Nombre" para compararlos
                strcpy(Autor1, Orden[j]->ApellAutor);
                if (Orden[j]->NomAutor != NULL)
                {
                    strcat(Autor1, ", ");
                    strcat(Autor1, Orden[j]->NomAutor);
                }
                strcpy(Autor2, aux->ApellAutor);
                if (aux->NomAutor != NULL)
                {
                    strcat(Autor2, ", ");
                    strcat(Autor2, aux->NomAutor);
                }
                comparador = strcmp(Autor1, Autor2);
            }
            else
            {
                // Si el campo es "por titulo", se compara directamente
                comparador = strcmp(Orden[j]->Obra, aux->Obra);
            }

            /***********************************************************************
             * Para ordenar:                                                       *
             * Si Autor1 es igual que Autor2 -> comparador = 0                     *
             * Si Autor1 es lexicográficamente menor que Autor2 -> comparador < 0  *
             * Si Autor1 es lexicográficamente mayor que Autor2 -> comparador > 0  *
             **********************************************************************/

            if (comparador <= 0)
                break;
            Orden[j + 1] = Orden[j];
            j--;
        }
        Orden[j + 1] = aux;
    }

    // Calcular el tiempo de finalización
    gettimeofday(&fin, NULL);
    Estadisticas.TiempoInsercion = DifTiempo(inicio, fin);

    return (Orden);
}