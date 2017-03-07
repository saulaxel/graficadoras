/**********************************************************/
/* Biblioteca : graficadora                               */
/* DescripciOn: Define funciones comunes para ser usadas  */
/*              por los programas para graficar.          */
/**********************************************************/

#ifndef _GRAFICADORA_H
#define _GRAFICADORA_H

/*========================*
 * Bibliotecas requeridas *
 *========================*/

#include <graphics.h>
#include <math.h>

#ifdef __unix__
    #include "../acentos.h"
#else // Probablemente windows
    #include "..\acentos.h"
#endif // Fin __unix__

/*==============*
 * Definiciones *
 *==============*/

#define TAMX 640
#define TAMY 480

#define TAMFLECHA 20

#define ESPACIO 10

/*=======================*
 * Prototipos de funciOn *
 *=======================*/

void abrirGraficadora(void);
void cerrarGraficadora(void);
void pintarEjes(void);
void pintarFuncion();

void abrirGraficadora(void) {
    int gd = DETECT, gm;

    initgraph(&gd, &gm, NULL);

    pintarEjes();

    return;
}

void cerrarGraficadora(void) {
    closegraph();

    return;

}

void pintarEjes(void) {
    // Eje X
    line(ESPACIO, TAMY / 2, TAMX - ESPACIO, TAMY / 2);
    line(ESPACIO, TAMY / 2, ESPACIO + TAMFLECHA, TAMY / 2 + TAMFLECHA);
    line(ESPACIO, TAMY / 2, ESPACIO + TAMFLECHA, TAMY / 2 - TAMFLECHA);
    line(TAMX - ESPACIO, TAMY / 2, TAMX - ESPACIO - TAMFLECHA, TAMY / 2 +
            TAMFLECHA);
    line(TAMX - ESPACIO, TAMY / 2, TAMX - ESPACIO - TAMFLECHA, TAMY / 2 -
            TAMFLECHA);

    // Eje Y
    line(TAMX / 2, ESPACIO, TAMX / 2, TAMY - ESPACIO);
    line(TAMX / 2, ESPACIO, TAMX / 2 + TAMFLECHA, ESPACIO +
            TAMFLECHA);
    line(TAMX / 2, ESPACIO, TAMX / 2 - TAMFLECHA,
            ESPACIO + TAMFLECHA);
    line(TAMX / 2, TAMY - ESPACIO, TAMX / 2 +
            TAMFLECHA, TAMY - ESPACIO - TAMFLECHA);
    line(TAMX / 2, TAMY - ESPACIO, TAMX / 2 -
            TAMFLECHA, TAMY - ESPACIO - TAMFLECHA);

    return;
}

void pintarFuncion(int* (*f)(float x)) {
    int x, *y_ant, *y_act;

    x = ESPACIO - 1;

    y_act = f( (float)( x - TAMX / 2  )  );

    if( (y_ant = (int *) malloc(y_act[1] * sizeof(int))) == NULL ) {
        exit(0);
    }

    for(int i = 0; i <= y_act[0]; i++) {
        y_ant[i] = y_act[i];
    }

    for( x = ESPACIO; x < TAMX - ESPACIO; x++ ) {
        y_act = f( (float)( x - TAMX / 2  )  );
        for(int i = 1; i <= y_act[0]; i++) {
            if( y_ant[i] < TAMY / 2 - ESPACIO &&
                    y_act[i] < TAMY / 2 - ESPACIO &&
                    y_ant[i] > -TAMY / 2 + ESPACIO &&
                    y_act[i] > -TAMY / 2  + ESPACIO ) {
                line(
                        x - 1,
                        -y_ant[i] + TAMY / 2,
                        x,
                        -y_act[i] + TAMY / 2

                    );

            }
            for(int s = 0; s <= y_act[0]; s++) {
                y_ant[s] = y_act[s];

            }

        }

    }

    free(y_ant);
}

#endif // _GRAFICADORA_H
