/*****************************************
 * Nombre: Quicksort
 * Argumentos: DISCO *Ficha:       Array de las fichas de discos
 *             int campo:          Campo por el que hacer la ordenación (Título o Autor)
 * Descripción: Ordena el array de fichas de discos en un doble puntero a las fichas de Discos,
 *              por lo que el movimiento de datos se reduce al cambio de punteros.
 *              Se usa el algoritmo de ordenación de Quicksort.
 * Reglas de uso: 
 * Código de Retorno: DISCO **: Doble puntero ordenado por el criterio pedido a las fichas de discos.
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "../Discoteca.h"

static int Qcmp(DISCO *Orden1,DISCO *Orden2,int Campo)
{
    char Autor1[256], Autor2[256];

    if (Campo == ORDEN_POR_AUTOR) {
        strcpy(Autor1,Orden1->ApellAutor);
        if (Orden1->NomAutor != NULL) {
            strcat(Autor1,", ");
            strcat(Autor1,Orden1->NomAutor);
        }
        strcpy(Autor2,Orden2->ApellAutor);
        if (Orden2->NomAutor != NULL) {
            strcat(Autor2,", ");
            strcat(Autor2,Orden2->NomAutor);
        }
        return(strcmp(Autor1,Autor2));
    }
    else
        return(strcmp(Orden1->Obra,Orden2->Obra));
}

static void QSort(DISCO **Orden,int izquierda, int derecha, int Campo)
{
    DISCO *auxiliar;
    int i, j;

    if (izquierda < derecha) {
        i = izquierda+1;
        j = derecha;
	    while(i <= j) {
            for(;(i<=j) && Qcmp(Orden[i],Orden[izquierda],Campo)<=0;i++);
            for(;(i<=j) && Qcmp(Orden[j],Orden[izquierda],Campo)>=0;j--);
	        if (i<j) {
			    auxiliar = Orden[i];
			    Orden[i] = Orden[j];
			    Orden[j] = auxiliar;
			    j--;
			    i++;
		    }
	    }
	    auxiliar = Orden[izquierda];
	    Orden[izquierda] = Orden[j];
	    Orden[j] = auxiliar;

        QSort (Orden, izquierda, j-1,Campo);
        QSort (Orden, j+1, derecha,Campo);
    }

    return;
}

DISCO **Quicksort(DISCO *Ficha, int Campo)
{
    DISCO **Orden;
    struct timeval inicio, fin;

    gettimeofday(&inicio,NULL);
    Orden=InitOrden(Ficha);

    QSort(Orden,0,Estadisticas.NumeroFichas-1,Campo);
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoQuicksort=DifTiempo(inicio,fin);

    return(Orden);
}