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
    //Añade aquí la definición del resto de variables necesarias
    
    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);
    char Autor1[256], Autor2[256];

    //Código del Alumno del método de ordenación de la Burbuja
    if(Campo == ORDEN_POR_TITULO){
        for(i = 0; i < n - 1; i++){
            for(j = 0; j < n - i - 1; j++ ){
                if(strcmp(Orden[j]->Obra, Orden[j + 1]->Obra) > 0){
                    pAux = Orden[j];
                    Orden[j] = Orden[j + 1];
                    Orden[j + 1] = pAux;
                }
            }
        }
    } else if(Campo == ORDEN_POR_AUTOR){
        
        for(i = 0; i < n - 1; i++){
            for(j = 0; j < n - i - 1; j++ ){
                strcpy(Autor1,Orden[j]->ApellAutor);
                if (Orden[j]->NomAutor != NULL) {
                    strcat(Autor1,", ");
                    strcat(Autor1,Orden[j]->NomAutor);
                }
                strcpy(Autor2,Orden[j+1]->ApellAutor);
                if (Orden[j+1]->NomAutor != NULL) {
                    strcat(Autor2,", ");
                    strcat(Autor2,Orden[j+1]->NomAutor);
                }
                if(strcmp(Autor1, Autor2) > 0){
                    pAux = Orden[j];
                    Orden[j] = Orden[j + 1];
                    Orden[j + 1] = pAux;
                }
            }
        }        
    }
    gettimeofday(&fin, NULL);
    Estadisticas.TiempoBurbuja=DifTiempo(inicio,fin);

    return(Orden);
}