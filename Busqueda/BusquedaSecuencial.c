/*****************************************
 * Nombre: BusquedaSecuencial
 * Argumentos: DISCO *Fichas:       Array de las fichas de discos
 * Descripción: Después de capturar los apellidos de un autor, busca las fichas de discos de ese autor
 *              por el método de búsqueda por selección.
 *              La comparación de los apellidos se hace en mayúsculas. 
 *              Después se muestran los resultados en una pantalla de scroll.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Busqueda.h"

void BusquedaSecuencial(DISCO *Fichas)
{
    char *Autor;
    char CopiaAutor[256];
    DISCO **Resultado=NULL;
    int i,j,n;
    int DimResultado, Hallados=0;
    struct timeval inicio, fin;

    if ((Autor=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    Resultado=(DISCO **)malloc(sizeof(DISCO *)*10);
    DimResultado=10;
    n=strlen(Autor);

    for(i=0;i<Estadisticas.NumeroFichas;i++) {
        for(j=0;Fichas[i].ApellAutor[j] != 0;j++) {
            CopiaAutor[j]=Fichas[i].ApellAutor[j];
            if (CopiaAutor[j] < 'a')
                CopiaAutor[j]+=' ';
        }
        if (strncmp(CopiaAutor,Autor,n) == 0) {
            if (DimResultado == Hallados+1) {
                DimResultado+=10;
                Resultado=realloc(Resultado,sizeof(DISCO *)*DimResultado);
            }
            Resultado[Hallados]=Fichas+i;
            Hallados++;
        }
    }

    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBusquedaSecuencial=DifTiempo(inicio,fin);

    if (Hallados == 0) {
        VentanaError("No hay autores que cumplan el criterio");
        return;
    }
    Listado1(Resultado,Hallados,Fichas);
    free(Resultado);
    return;
    
}