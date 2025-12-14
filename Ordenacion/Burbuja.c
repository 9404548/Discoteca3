/*****************************************
 * Nombre: Burbuja
 * Argumentos: DISCO *Ficha:       Array de las fichas de discos
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de discos en un doble puntero a las fichas de discos,
 *              por lo que el movimient de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de la burbuja.
 * Reglas de uso: 
 * Código de Retorno: DISCO **: Doble puntero ordenado por el criterio pedido a las fichas de discos.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

DISCO **Burbuja(DISCO *Ficha,int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;
    int i,j;
    int n = Estadisticas.NumeroFichas;
    DISCO *pAux;
    
    gettimeofday(&inicio,NULL);
    // Se inicializa el array de fichas
    Orden=InitOrden(Ficha);
    // Variables para la comparación de autores
    char Autor1[256], Autor2[256];

    // Si queremos ordenar las fichas por título
    if(Campo == ORDEN_POR_TITULO){
        // Bucle de la burbuja que recorre todo el array
        for(i = 0; i < n - 1; i++){
            // Bucle que realiza las comparaciones entre las fichas vecinas
            for(j = 0; j < n - i - 1; j++ ){
                // Si la ficha izquierda es mayor que la derecha, se intercambian
                if(strcmp(Orden[j]->Obra, Orden[j + 1]->Obra) > 0){
                    pAux = Orden[j];
                    Orden[j] = Orden[j + 1];
                    Orden[j + 1] = pAux;
                }
            }
        }
    // si queremos ordenar las fichas por autor
    } else if(Campo == ORDEN_POR_AUTOR){
        
        // Bucle de la burbuja que recorre todo el array
        for(i = 0; i < n - 1; i++){
            // Bucle que realiza las comparaciones entre las fichas vecinas
            for(j = 0; j < n - i - 1; j++ ){
                // Aquí se construyen los nombres completos de los autores, copia el apellido del autor en Autor1
                strcpy(Autor1,Orden[j]->ApellAutor);
                if (Orden[j]->NomAutor != NULL) {
                    // Si el nombre del autor no es NULL, se concatena con una coma primero el apellido y luego el nombre
                    strcat(Autor1,", ");
                    strcat(Autor1,Orden[j]->NomAutor);
                }
                // Aquí lo mismo para la ficha vecina, se copia en Autor2
                strcpy(Autor2,Orden[j+1]->ApellAutor);
                if (Orden[j+1]->NomAutor != NULL) {
                    strcat(Autor2,", ");
                    strcat(Autor2,Orden[j+1]->NomAutor);
                }
                // Se realiza un intercambio siempre que la ficha izquierda sea mayor que la ficha derecha
                // de manera que la ficha mayor siempre quede a la derecha del todo en cada iteración
                if(strcmp(Autor1, Autor2) > 0){
                    pAux = Orden[j];
                    Orden[j] = Orden[j + 1];
                    Orden[j + 1] = pAux;
                }
            }
        }        
    }
    gettimeofday(&fin, NULL);
    // Se actualiza el tiempo de ordenación en las estadísticas
    Estadisticas.TiempoBurbuja=DifTiempo(inicio,fin);

    // Devuelve el array ordenado
    return(Orden);
}