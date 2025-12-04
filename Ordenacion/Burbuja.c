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
    char* nombre = (char*)malloc(sizeof(char)*100);
    char* apellido = (char*)malloc(sizeof(char)*100);
    char nombreCompleto1[100] = "";
    char nombreCompleto2[100] = "";
    DISCO *pAux;
    //Añade aquí la definición del resto de variables necesarias
    
    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);
    pAux = Orden[0];
    //Código del Alumno del método de ordenación de la Burbuja
    if(Campo == ORDEN_POR_TITULO){
        for(i = 1; i <= n - i; i++){
            for(j = 0; j < n - i; j++ ){
                if(strcmp(Orden[j]->Obra, Orden[j + 1]->Obra) > 0){
                    pAux = Orden[j];
                    Orden[j] = Orden[j + 1];
                    Orden[j + 1] = pAux;
                }
            }
        }
    } else if(Campo == ORDEN_POR_AUTOR){
        for(i = 1; i <= n - i; i++){
            for(j = 0; j < n - i; j++ ){

                *nombre = *(Orden[j]->ApellAutor);
                *apellido = *(Orden[j]->NomAutor);
                strcat(strcat(strcat(nombreCompleto1, nombre), ", "), apellido);

                *nombre = *(Orden[j+1]->ApellAutor);
                *apellido = *(Orden[j+1]->NomAutor);
                strcat(strcat(strcat(nombreCompleto2, nombre), ", "), apellido);

                if(strcmp(nombreCompleto1, nombreCompleto2) > 0){
                    pAux = Orden[j];
                    Orden[j] = Orden[j + 1];
                    Orden[j + 1] = pAux;
                }
            }
        }        
    }
    free(nombre);
    free(apellido);
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBurbuja=DifTiempo(inicio,fin);

    return(Orden);
}