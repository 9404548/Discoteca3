/*****************************************
 * Nombre: BusquedaBinaria
 * Argumentos: LIBRO *Fichas:       Array de las fichas de libros
 * Descripción: Después de capturar los apellidos de un autor, busca las fichas de libros de ese autor,
 *              por el método de búsqueda binaria
 *              La comparación de los apellidos se hace en mayúsculas. 
 *              Después se muestran los resultados en una pantalla de scroll.
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: JMSM (Sept-24)
 *****************************************/

#include "Busqueda.h"

char lowercase(char c){
    if(c >= 'A' && c <= 'Z'){
        c += 32;
    }
    return c;
}

void BusquedaBinaria(DISCO *Fichas)
{
    char *Autor;
    DISCO **Resultado=NULL;
    DISCO **Orden=NULL;
    int Hallados=0;
    struct timeval inicio, fin;
    bool Encontrado;

    // Añadir aquí la definición del resto de variables usadas

    if ((Autor=LeerAutor()) == NULL)
        return;

    gettimeofday(&inicio,NULL);

    Orden=Quicksort(Fichas, ORDEN_POR_AUTOR);

    //Código del alumno del Algoritmo de Búsqueda Binaria
    int indiceBusqueda = Estadisticas.NumeroFichas / 2;
    int comparacion = 0;
    char Apellido[256];
    int i, j, maxIteraciones, limiteInferior, limiteSuperior;
    DISCO *pAux;

    maxIteraciones = 0;
    i = 1;
    do{
        maxIteraciones++;
        i *=2;
    }while(i < Estadisticas.NumeroFichas);
    maxIteraciones++;

    for(i = 0; i < maxIteraciones; i++){ // Este bucle encuentra una instancia del apellido buscado
        strcpy(Apellido, Orden[indiceBusqueda]->ApellAutor);
        for(j = 0; Apellido[j]; i++){
            Apellido[j] = lowercase(Apellido[j]);
        }

        if((comparacion = strcmp(Autor, Apellido)) == 0){
            Encontrado = true;
            Hallados++;
            break;
        }
        else if(comparacion < 0) indiceBusqueda /= 2;
        else indiceBusqueda += indiceBusqueda / 2;
    }
    
    if(Encontrado){
        for(i = indiceBusqueda - 1; i > -1; i--){
            strcpy(Apellido, Orden[i]->ApellAutor);
            for(j = 0; Apellido[j]; j++){
                Apellido[j] = lowercase(Apellido[j]);
            }
            if(strcmp(Autor, Apellido) == 0){
                Hallados++;
                continue;
            }
            limiteInferior = i + 1;
        }

        for(i = indiceBusqueda + 1; i < Estadisticas.NumeroFichas; i++){
            strcpy(Apellido, Orden[i]->ApellAutor);
            for(j = 0; Apellido[j]; j++){
                Apellido[j] = lowercase(Apellido[j]);
            }
            if(strcmp(Autor, Apellido) == 0){
                Hallados++;
                continue;
            }
            limiteSuperior = i - 1;
        }

        for(i = 0; i < Hallados; i++){
            Resultado[i] = Orden[limiteInferior + i];
        }
    }
    

    free(Orden);
    
    gettimeofday(&fin,NULL);
    Estadisticas.TiempoBusquedaBinaria=DifTiempo(inicio,fin);

    if (Encontrado == false) {
        VentanaError("No hay autores que cumplan el criterio");
        return;
    }
    
    Listado1(Resultado,Hallados,Fichas);
    free(Resultado);
    return;
    
}