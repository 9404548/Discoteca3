/*****************************************
 * Nombre: Seleccion
 * Argumentos: DISCO *Ficha:       Array de las fichas de discos
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de discos en un doble puntero a las fichas de Discos,
 *              por lo que el movimiento de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Selección.
 * Reglas de uso: 
 * Código de Retorno: DISCO **: Doble puntero ordenado por el criterio pedido a las fichas de discos.
 * Programador: JMSM (Sept-25)
 *****************************************/

#include "../Discoteca.h"

DISCO **Seleccion(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    int i, j, min;
    char Autor1[100], Autor2[100];
    int n = Estadisticas.NumeroFichas;
    DISCO *pAux;
    // Añade aquí la definición del resto de variables necesarias

    gettimeofday(&inicio, NULL);
    Orden = InitOrden(Ficha);

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
                // Concateno el apellido y el nombre de autores
                strcpy(Autor1, Orden[j]->ApellAutor);
                if(Orden[j]->NomAutor != NULL){
                    strcat(Autor1, ", ");
                    strcat(Autor1, Orden[j]->NomAutor);
                }
                // Concateno el apellido y el nombre del autor que es el menor
                strcpy(Autor2, Orden[min]->ApellAutor);
                if(Orden[min]->NomAutor != NULL){
                    strcat(Autor2, ", ");
                    strcat(Autor2, Orden[min]->NomAutor);
                }
                // Se compara y si es menor, se actualiza min
                if(strcmp(Autor1, Autor2) < 0){
                    min = j;
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

    // Devuelve el array ordenado
    return (Orden);
}