/*****************************************
 * Nombre: VerEstadisticas
 * Argumentos: 
 * Descripción: Muestra los datos de Estadisticas actuales
 * Reglas de uso: 
 * Código de Retorno:
 * Programador: JMSM (Sept-24)
 *****************************************/

//Include del módulo funcional
#include "Ventanas.h"

void VerEstadisticas()
{
    static WINDOW *Westad;

    // Se crea y dibuja la ventana de Estadisticas
    if (Westad == NULL) {
        Westad=newwin(14,76,3,2);
        DibujarEstadisticas(Westad);
    }
    touchwin(Westad);
    wrefresh(Westad);

    // Se limpia cada dato y después se reescribe
    mvwprintw(Westad,2,22,"                                                     ");
    mvwprintw(Westad,2,22,"%s",Estadisticas.Fichero);
    mvwprintw(Westad,3,43,"                                 ");
    mvwprintw(Westad,3,43,"%d",Estadisticas.NumeroFichas);
    mvwprintw(Westad,4,43,"                                 ");
    mvwprintw(Westad,4,43,"%d",Estadisticas.MaxFichas);
    mvwprintw(Westad,5,43,"                                ");
    mvwprintw(Westad,5,43,"%d",Estadisticas.TiempoCarga);
    mvwprintw(Westad,6,43,"                                ");
    mvwprintw(Westad,6,43,"%d",Estadisticas.TiempoSeleccion);
    mvwprintw(Westad,7,43,"                                ");
    mvwprintw(Westad,7,43,"%d",Estadisticas.TiempoBurbuja);
    mvwprintw(Westad,8,43,"                                ");
    mvwprintw(Westad,8,43,"%d",Estadisticas.TiempoInsercion);
    mvwprintw(Westad,9,43,"                                ");
    mvwprintw(Westad,9,43,"%d",Estadisticas.TiempoQuicksort);
    mvwprintw(Westad,10,43,"                                ");
    mvwprintw(Westad,10,43,"%d",Estadisticas.TiempoBusquedaSecuencial);
    mvwprintw(Westad,11,43,"                                ");
    mvwprintw(Westad,11,43,"%d",Estadisticas.TiempoBusquedaBinaria);
    mvwprintw(Westad,12,43,"                            ");
    mvwprintw(Westad,12,43,"%d",Estadisticas.TiempoBusquedaArbol);
    touchwin(Westad);
    wrefresh(Westad);

    // Mensaje Final
    VentanaError("Estadisticas actuales");
    return;
}