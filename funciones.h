
/**********************************************************/
/* Biblioteca : funciones                                 */
/* DescripciOn: Define funciones comunes para ser usadas  */
/*              por los programas para graficar.          */
/**********************************************************/

#ifndef _FUNCIONES_H
#define _FUNCIONES_H

/*=======================*
 * Bibliotecas incluidas *
 *=======================*/

#include <stdbool.h>
#include "acentos.h"

/*=======================================*
 * Definiciones de macros y de variables *
 *=======================================*/

#define NUM_FUNCIONES 8

const char *DESC_FUNC[NUM_FUNCIONES] = {
    "Polinomica (M" A "ximo grado 3)" , // 1
    "Eliptica"                        , // 2
    "Hiperbolica"                     , // 3
    "Seno"                            , // 4
    "Coseno"                          , // 5
    "Tangente"                        , // 6
    "Exponencial"                     , // 7
    "Logaritnica"                       // 8
};

/*-* Funciones *-*/
int16_t func_polinomica(float f, bool init_values, ...);
int16_t func_elipse(float f, bool init_values, ...);
int16_t func_hiperbola(float f, bool init_values, ...);
int16_t func_sin(float f, bool init_values, ...);
int16_t func_cos(float f, bool init_values, ...);
int16_t func_tan(float f, bool init_values, ...);
int16_t func_exponencial(float f, bool init_values, ...);
int16_t func_logaritmo(float f, bool init_values, ...);

/*-* Arreglo que contiene a las funciones anteriores *-*/
int16_t (*const ARR_FUNC[NUM_FUNCIONES])(float f, bool init_values, ...) = {
    func_polinomica,
    func_elipse,
    func_hiperbola,
    func_sin,
    func_cos,
    func_tan,
    func_exponencial,
    func_logaritmo
};

/*===================*
 * SecciOn de cOdigo *
 *===================*/

int16_t func_polinomica(float f, bool init_values, ...){ return 0; }
int16_t func_elipse(float f, bool init_values, ...){ return 0; }
int16_t func_hiperbola(float f, bool init_values, ...){ return 0; }
int16_t func_sin(float f, bool init_values, ...){ return 0; }
int16_t func_cos(float f, bool init_values, ...){ return 0; }
int16_t func_tan(float f, bool init_values, ...){ return 0; }
int16_t func_exponencial(float f, bool init_values, ...){ return 0; }
int16_t func_logaritmo(float f, bool init_values, ...){ return 0; }

#endif // Fin _FUNCIONES_H
