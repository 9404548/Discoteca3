/*****************************************
 * Nombre: Listado1
 * Argumentos: DISCO **Orden:       Doble puntero a un array de punteros de discos con un orden
 *             int NumeroFichas:    Numero de Fichas que hay en el array
 *             DISCO *Fichas:       Array con los discos
 * Descripción: Muestra en la ventana del listado los datos principales de los discos
 *              con scroll vertical. Se permite movimientos con las flechas arriba y abajo
 *              o con PgDn o PgUp
 * Reglas de uso: 
 * Código de Retorno: N/A
 * Programador: JMSM (Sept-24)
 *****************************************/
 
// Se incluye el include de la unidad funcional
#include "Listados.h"

void Listado2(DISCO **Orden,int NumeroFichas, DISCO *Fichas)
{
    static WINDOW *Wscroll=NULL;        // Ventana en la que se van a mostrar los datos
    LISTA *EnPantalla=NULL;             // TAD Lista para los discos en pantalla
    PILA *Anteriores=NULL;              // TAD PILA para los discos anteriores a los que están en pantalla
    COLA *Siguientes=NULL;              // TAD COLA para los discos siguientes a los que están en pantalla

    int Actual,Longitud;                // Disco marcado y número de disco en pantalla
    int i,j;
    char *Linea, Autor[256];            // Puntero a una línea de pantalla y "Apellidos, Nombre"
    int Tecla;                          // Tecla pulsada

    
    // Creación de los TADs
    Anteriores=CrearPila();
    if ((EnPantalla=CrearLista()) == NULL) {
        VentanaError("Error al crear la Lista");
        return;
    }
    if ((Siguientes=CrearCola()) == NULL) {
        VentanaError("Error al crar la Cola");
        return;
    }

    // Se formatean las líneas de pantalla de todos los discos y se encolan en Siguientes (no hay todavía nada en pantalla)
    for(i=0;i<NumeroFichas;i++) {
        if ((Linea=malloc(80)) == NULL) {
            VentanaError("Error al asignar memoria para el Listado");
            return;
        }
        strcpy(Autor,Orden[i]->ApellAutor);
        if (Orden[i]->NomAutor != NULL) {
                strcat(Autor,", ");
                strcat(Autor,Orden[i]->NomAutor);
        }
        j=(Orden[i]-Fichas)+1;
        sprintf(Linea,"%4d %-40.40s %-27.27s",j,Orden[i]->Obra,Autor);
        Encolar(Siguientes,Linea);
    }

    // Se crea la ventana de Scroll si no se ha hecho ya
    if (Wscroll == NULL) {
        Wscroll=newwin(16,76,2,2);
        DibujarScroll(Wscroll);
    }

    // Se activa la lectura de teclas múltiples
    keypad(Wscroll,true);
    // El disco actual es el primer disco en pantalla
    Actual=0;

    // Bucle infinito hasta que se pulse ESC
    while(true) {
        // Se asegura que en la lista EnPantalla hay 10 líneas (sacándolas de Siguientes)
        while ((Longitud=LongitudLista(EnPantalla)) < 10) {
            if (EsColaVacia(Siguientes) == true)
                break;
            else {
                Linea=Desencolar(Siguientes);
                InsertarListaDerecha(EnPantalla,Linea);
            }
        }
        // Se imprimen las líneas del TAD EnPantalla marcando la línea actual de otro color
        // Para ello, como es una lista, se van sacando las líneas por la izquierda y se vuelven a insertar por la derecha
        for(i=0;i<10;i++) {
            if (i >= Longitud)
                mvwprintw(Wscroll,i+4,2,"                                                                          ");
            else {
                Linea=BorrarListaIzquierda(EnPantalla);
                if (i == Actual)
                    wcolor_set(Wscroll,7,NULL);
                mvwprintw(Wscroll,i+4,2,"%s",Linea);
                if (i == Actual)
                    wcolor_set(Wscroll,9,NULL);
                InsertarListaDerecha(EnPantalla,Linea);
            }
        }
        // Se refresca la ventana de Scroll
        touchwin(Wscroll);
        wrefresh(Wscroll);
        // Se lee una tecla que sea: ESC, UP, DOWN, PgDn, PgUp o 'beep'
        while(((Tecla=wgetch(Wscroll)) != KEY_ESC) && (Tecla != KEY_UP) && (Tecla != KEY_DOWN) && (Tecla != KEY_PPAGE) && (Tecla != KEY_NPAGE))
            beep();
        // Si es ESC, fin del bucle
        if (Tecla == KEY_ESC)
            break;
        // Acciones de las teclas
        switch(Tecla) {
        // UP: Se sube actual una línea. Si actual es la primera línea, se saca una línea de la pila Anteriores y se inserta en
        // la Lista EnPantalla por la izquierda. Luego se saca una línea de EnPantalla por la Derecha y se inserta como Cabecera
        // en la cola Siguientes
        case KEY_UP:
            if (Actual == 0) {
                if (EsPilaVacia(Anteriores) == true)
                    beep();
                else {
                    Linea=BorrarListaDerecha(EnPantalla);
                    InsertarCabecera(Siguientes,Linea);
                    Anteriores=Desapilar(Anteriores,(void **) &Linea);
                    InsertarListaIzquierda(EnPantalla,Linea);
                }
            }
            else
                Actual--;
            break;
        // DOWN: Se baja actual una línea. Si actual es la última línea, se saca una línea de EnPantalla por la Izquiera y
        // se Apila en Anteriores. Al principio del bucle se saca una línea de Siguientes.
        // en la cola Siguientes
        case KEY_DOWN:
            if (Actual == 9) {
                if (EsColaVacia(Siguientes) == true)
                    beep();
                else {
                    Linea=BorrarListaIzquierda(EnPantalla);
                    Anteriores=Apilar(Anteriores,Linea);
                }
            }
            else {
                if ((Actual+1) >= LongitudLista(EnPantalla))
                    beep();
                else
                    Actual++;
            }
            break;
        // PgUp: Se sacan todas las líneas de EnPantalla por la Derecha y se inserta en Siguientes como Cabecera.
        // Luego se desapilan de Anteriores 10 líneas (o las que haya) y se intertan en EnPantalla por la Izquierda
        case KEY_PPAGE:
            for(i=0;i<10;i++) {
                if (EsPilaVacia(Anteriores) == true) {
                    if (i == 0)
                        beep();
                    break;
                }
                Linea=BorrarListaDerecha(EnPantalla);
                InsertarCabecera(Siguientes,Linea);
                Anteriores=Desapilar(Anteriores,(void **) &Linea);
                InsertarListaIzquierda(EnPantalla,Linea);
            }
            Actual=0;
            break;
        // PgDn: Se sacan las líneas de EnPantalla por la izquierda y se Apilan en Anteriores.
        // Al principio del bucle se cargan las 10 siguientes líneas de Siguientes
        case KEY_NPAGE:
            if (EsColaVacia(Siguientes) == true)
                beep();
            else {
                while(EsListaVacia(EnPantalla) == false) {
                    Linea=BorrarListaIzquierda(EnPantalla);
                    Anteriores=Apilar(Anteriores,Linea);
                }
                Actual=0;
            }
            break;
        }
    }
    // Fin del programa. Hay que liberar los TADs
    // Se borran las líneas de Anteriores, desapilándolas y liberando el espacio de la línea formateada
    if (Anteriores != NULL) {
        while(EsPilaVacia(Anteriores) == false) {
            Anteriores=Desapilar(Anteriores,(void **) &Linea);
            free(Linea);
        }
    }
    // Se borran las líneas de EnPantalla, Borrándolas por la Izquierda y liberando el espacio de la línea formateada
    if (EnPantalla != NULL) {
        while(EsListaVacia(EnPantalla) == false) {
            Linea=BorrarListaIzquierda(EnPantalla);
            free(Linea);
        }
        free(EnPantalla);
    }
    // Se borran las líneas de Siguientes, desencolándolas y liberando el espacio de la línea formateada
    if (Siguientes != NULL) {
        while(EsColaVacia(Siguientes) == false) {
            Linea=Desencolar(Siguientes);
            free(Linea);
        }
        free(Siguientes);
    }

    return;
}