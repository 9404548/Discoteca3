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
// static int comparar(DISCO *a, DISCO *b, int Campo)
// {
//     if (Campo == ORDEN_POR_AUTOR) {
//         char Autor1[256], Autor2[256];
//         strcpy(Autor1, a->ApellAutor);
//         if (a->NomAutor != NULL) {
//             strcat(Autor1, ", ");
//             strcat(Autor1, a->NomAutor);
//         }
//         strcpy(Autor2, b->ApellAutor);
//         if (b->NomAutor != NULL) {
//             strcat(Autor2, ", ");
//             strcat(Autor2, b->NomAutor);
//         }
//         return strcmp(Autor1, Autor2);
//     } else {
//         return strcmp(a->Obra, b->Obra);
//     }
// }

DISCO **Seleccion(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    int i, j, min, comp;
    int n = Estadisticas.NumeroFichas;
    DISCO *pAux;
    // Añade aquí la definición del resto de variables necesarias

    gettimeofday(&inicio, NULL);
    Orden = InitOrden(Ficha);
    pAux = Orden[0];
    // Bucle que avanza de casilla en casilla
    for (i = 0; i < n - 1; i++)
    {
        // Suponemos que el primer elemento es el menor
        min = i;
        // Bucle para buscar si hay alguien menor
        for (j = i + 1; j < n; j++)
        {
            if (Campo == ORDEN_POR_TITULO)
            {
                // Comparamos la primera obra que hemos puesto como menor con las demás
                if (strcmp(Orden[j]->Obra, Orden[min]->Obra) < 0)
                {
                    // Si hay una menor actualizamos min
                    min = j;
                }
            }
            else if (Campo == ORDEN_POR_AUTOR)
            {
                // Comparamos los apellidos
                comp = strcmp(Orden[j]->ApellAutor, Orden[min]->ApellAutor);
                if (comp < 0)
                {
                    // El menor de los apellidos
                    min = j;
                }
                // Si el apellido es igual
                else if (comp == 0)
                {
                    // Comparamos con el nombre
                    if (strcmp(Orden[j]->NomAutor, Orden[min]->NomAutor) < 0)
                    {
                        // El menor de los nombres
                        min = j;
                    }
                }
            }
        }
        // Si encontramos a alguien mejor, lo traigo a la posicion i
        if (min != i)
        {
            // Cambio
            pAux = Orden[i];
            Orden[i] = Orden[min];
            Orden[min] = pAux;
        }
    }
    gettimeofday(&fin, NULL);
    Estadisticas.TiempoSeleccion = DifTiempo(inicio, fin);

    return (Orden);
}