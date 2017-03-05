/**********************************************************/
/* Biblioteca : graficadora                                */
/* DescripciOn: Define funciones comunes para ser usadas  */
/*              por los programas para graficar.          */
/**********************************************************/

#ifndef _GRAFICADORA_H
#define _GRAFICADORA_H

/*========================*
 * Bibliotecas requeridas *
 *========================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __unix__
    #include "../acentos.h"
#else // Probablemente windows
    #include "..\acentos.h"
#endif // Fin __unix__

/*==============*
 * Definiciones *
 *==============*/
#define ESCALA 2   // 2 columnas de texto representan una unidad en x

/*==================*
 * Plano cartesiano *
 *==================*/
// Apuntador doble a caracter para representar el plano
char **panel;
// Dimensiones del plano ( dependen de la pantalla )
int16_t TAM_X;
int16_t TAM_Y;

/*===========*
 * Funciones *
 *===========*/
bool establecerTamanioPanel(char **);            // Asigna tamanio dinAmicamente
void eliminaPanel(void);                         // Libera la memoria
void pintarEjes(void);                           // Pone carActeres en la matriz para representar los ejes
void pintarFuncion(int16_t * (*f)(double, bool, ...)); // Establece puntos en la matriz
void graficar(void);                             // Imprime la matriz a pantalla

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
