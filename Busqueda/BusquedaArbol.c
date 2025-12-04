/*****************************************
 * Nombre: BusquedaArbol
 * Argumentos: DISCO *Fichas:       Array de las fichas de discos
 * Descripción: Crea un árbol binario con las fichas de discos, con el criterio de los apellidos del autor en mayúsculas
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Busqueda.h"

static void LiberarArbol(ARBOL *Arbol)
{
    if (Arbol == NULL)
        return;
    LiberarArbol(Arbol->HojaDerecha);
    LiberarArbol(Arbol->HojaIzquierda);
    free(Arbol);
    return;
}

static int ComprobarArbol(ARBOL *Arbol, DISCO **Resultado, int indice, char *Autor, int n)
{
    int j;

    if (Arbol == NULL)
        return(indice);

    if ((j=strncmp(Arbol->Autor,Autor,n)) == 0) {
        Resultado[indice]=Arbol->Raiz;
        indice++;
        indice=ComprobarArbol(Arbol->HojaDerecha,Resultado,indice,Autor,n);
        indice=ComprobarArbol(Arbol->HojaIzquierda,Resultado,indice,Autor,n);
        free(Arbol);
    }
    else {
        if (j < 0) {
            LiberarArbol(Arbol->HojaIzquierda);
            indice=ComprobarArbol(Arbol->HojaDerecha,Resultado,indice,Autor,n);
            free(Arbol);
        }
        else {
            LiberarArbol(Arbol->HojaDerecha);
            indice=ComprobarArbol(Arbol->HojaIzquierda,Resultado,indice,Autor,n);
            free(Arbol);
        }
    }
    return(indice);
}

void BusquedaArbol(DISCO *Fichas)
{
    char *Autor;
    char CopiaAutor[256];
    ARBOL *Arbol=NULL,**Auxiliar;
    DISCO **Resultado=NULL;
    int i,j,n;
    int Hallados=0;
    struct timeval inicio, fin;

    if ((Autor=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    for(i=0;i<Estadisticas.NumeroFichas;i++) {
        for(j=0;Fichas[i].ApellAutor[j] != 0;j++) {
            CopiaAutor[j]=Fichas[i].ApellAutor[j];
            if (CopiaAutor[j] < 'a')
                CopiaAutor[j]+=' ';
        }
        
        for(Auxiliar=&Arbol;(*Auxiliar) != NULL;) {
            if (strcmp(CopiaAutor,(*Auxiliar)->Autor) < 0)
                Auxiliar=&((*Auxiliar)->HojaIzquierda);
            else
                Auxiliar=&((*Auxiliar)->HojaDerecha);
        }
        *Auxiliar=malloc(sizeof(ARBOL));
        strcpy((*Auxiliar)->Autor,CopiaAutor);
        (*Auxiliar)->Raiz=Fichas+i;
        (*Auxiliar)->HojaDerecha=NULL;
        (*Auxiliar)->HojaIzquierda=NULL;

    }
    
    Resultado=(DISCO **)malloc(sizeof(DISCO *)*Estadisticas.NumeroFichas);
    n=strlen(Autor);

    Hallados=ComprobarArbol(Arbol, Resultado, 0, Autor, n);
    Resultado[Hallados]=NULL;
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBusquedaArbol=DifTiempo(inicio,fin);

    if (Hallados == 0) {
        VentanaError("No hay autores que cumplan el criterio");
        return;
    }
    
    Listado1(Resultado,Hallados,Fichas);
    free(Resultado);
    return;
    
}