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


/* ====================================================== *
 * FunciOn    : establecerTamanioPanel                    *
 * DescripciOn: Verifica si los argumentos recibidos      *
 *              por lInea de comandos son enteros validos *
 *              y termina la ejecuciOn en caso de que no  *
 * ====================================================== */
bool establecerTamanioPanel(char **tamanio) {
    int allocated = true;

    if( (TAM_X = atoi(tamanio[0])) != 0 &&
        (TAM_Y = atoi(tamanio[1])) != 0 
      ) 
    {
        panel = (char **) calloc(TAM_X, sizeof(char *));

        if( panel ) {
            for(int i = 0; i < TAM_X; i++) {
                panel[i] = (char *) calloc(TAM_Y, sizeof(char));
                if( !panel[i] ) {
                    allocated = false;
                    break;
                }
            }
        } else {
            allocated = false;
        } 
    }

    return allocated;
}

/* ========================================================= *
 * FunciOn     :  pintarEjes                                 *
 * DescripciOn :  Limpia la matriz y pone en ella caracteres *
 *                que se en conjunto se asemejan a un par de *
 *                ejes cartesianos                           *
 * ========================================================= */
void pintarEjes(void) {
    int16_t n, m;

    // Se rellena todo el lienzo con espacios
    for(n = 0; n < TAM_X; ++n) {
        for(m = 0; m < TAM_Y; ++m){
            panel[n][m] = ' ';
        }
    }

    // Eje x
    for(n = 0; n < TAM_X; ++n) {
        panel[n][TAM_Y / 2] = '-';
    }

    // Eje y
    for(n = 0; n < TAM_Y; ++n) {
        panel[TAM_X / 2][n] = '|';
    }

    // Origen
    panel[TAM_X / 2][TAM_Y / 2] = '+';

    return;
}

void pintarFuncion( int16_t * (*f)(double, bool, ...) ) {
    int16_t *y;

    putchar('\n');

    y = f(0.0, false);

    for(int16_t i = 0; i < TAM_X; i++) {
        f(((double)i -TAM_X / 2 ) / ESCALA, false);
        for(int16_t j = 1; j <= y[0]; j++) {
            if( y[j] <= TAM_Y / 2 && y[j] >= -TAM_Y / 2 ) {
                panel[i][y[j] + TAM_Y / 2] = '*';
            }
        }
    }

    return;
}

void graficar(void) {
    int i, j;
    for(j = TAM_Y - 1; j >= 0; --j){
        for(i = 0; i < TAM_X; ++i){
#ifdef __unix__
            if(panel[i][j] == '*') {
                printf(PUNTO);
            } else {
                putchar(panel[i][j]);
            }
#else // Windows 
            putchar(panel[i][j]);
#endif // Fin __unix__
        }
        putchar('\n');
    }
    putchar('\n');

    getchar();

    return;
}

#endif // _GRAFICADORA_H

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
