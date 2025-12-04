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

void Listado1(DISCO **Orden,int NumeroFichas, DISCO *Fichas)
{
    static WINDOW *Wscroll=NULL;    // Ventana en la que se van a mostrar los datos
    int primero, actual;            // Primer disco en la pantalla y disco sobre el que está el cursor
    int i,j;
    char Autor[256];                // Espacio para "Apellidos, Nombre" del autor
    int Tecla;                      // Tecla pulsada

    // Se crea la ventana de scroll    
    if (Wscroll == NULL) {
        Wscroll=newwin(16,76,2,2);
        DibujarScroll(Wscroll);
    }

    // Se activa el leer teclas múltiples
    keypad(Wscroll,true);

    // Primer disco = Disco actual = 0 (El primero de Orden)
    primero=actual=0;

    // Bucle infinito hasta que se pulse ESC para salir
    while(true) {
        // Se imprimen 10 discos empezando en primero marcando el actual con otro color
        for(i=primero;i<primero+10;i++) {
            if (i >= NumeroFichas)
                mvwprintw(Wscroll,i-primero+4,2,"                                                                          ");
            else {
                if (i == actual)
                    wcolor_set(Wscroll,7,NULL);
                strcpy(Autor,Orden[i]->ApellAutor);
                if (Orden[i]->NomAutor != NULL) {
                    strcat(Autor,", ");
                    strcat(Autor,Orden[i]->NomAutor);
                }
                j=(Orden[i]-Fichas)+1;
                mvwprintw(Wscroll,i-primero+4,2,"%4d %-40.40s %-27.27s",j,Orden[i]->Obra,Autor);
                if (i == actual)
                    wcolor_set(Wscroll,9,NULL);
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
        // UP: Se sube actual una línea. Si actual es la primera línea en pantalla se inserta la línea anterior. Si es la primera línea beep.
        case KEY_UP:
            if (actual == primero) {
                if ((primero-1) < 0)
                    beep();
                else {
                    primero--;
                    actual=primero;
                }
            }
            else
                actual--;
            break;
        // DOWN: Se baja actual una línea. Si actual es la última línea en pantalla se inserta la siguiente línea. Si es la última línea beep.
        case KEY_DOWN:
            if (actual == NumeroFichas-1)
                beep();
            else {
                if (actual == (primero+9)) {
                    primero++;
                    actual++;
                }
                else
                    actual++;
            }
            break;
        // PgUp: Se cambia la pantalla con las 10 líneas anteriores. Si no hay 10 líneas se suben las que estén disponibles. Si actual es el
        // primer disco beep.
        case KEY_PPAGE:
            if (actual == 0)
                beep();
            else {
                primero-=10;
                if (primero < 0)
                    primero=0;
                actual=primero;
            }
            break;
        // PgDn: Se cambia la pantalla con las 10 líneas siguientes. Si no hay 10 líneas se bajan las que estén disponibles. Si actual es el
        // último disco beep.
        case KEY_NPAGE:
            if ((primero+10) >= NumeroFichas)
                beep();
            else {
                primero+=10;
                actual=primero;
            }
            break;
        }
    }

    // Fin. Es responsabilidad del programa principal restaurar la pantalla.
    return;
}