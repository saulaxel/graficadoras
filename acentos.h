
/**********************************************************/
/* Biblioteca : acentos.                                  */
/* DescripciOn: Define un conjunto de macros con          */
/*              secuencuas de escape que representan      */
/*              las vocales acentuadas. La definiciOn     */
/*              se hace tomando en cuenta al sistema.     */
/**********************************************************/

#ifndef _ACENTOS_H
#define _ACENTOS_H

#ifdef _WIN32

    #define CLEAR "cls"
    /*-* Letras minusculas *-*/
    #define A "\xA0"
    #define E "\x82"
    #define I "\xA1"
    #define O "\xA2"
    #define U "\xA3"
    #define N "\xA4"
    /*-* Letras mayusculas *-*/
    #define MA "\xB5"
    #define ME "\x90"
    #define MI "\xD6"
    #define MO "\xE0"
    #define MU "\xE9"
    #define MN "\xA5"

    #define Q  "\xA8"

#else // unix

    #define CLEAR "clear"
    /*-* Letras minusculas *-*/
    #define A "\u00E1"
    #define E "\u00E9"
    #define I "\u00ED"
    #define O "\u00F3"
    #define U "\u00FA"
    #define N "\u00F1"
    /*-* Letras mayusculas *-*/
    #define MA "\u00C1"
    #define ME "\u00C9"
    #define MI "\u00CD"
    #define MO "\u00D3"
    #define MU "\u00DA"
    #define MN "\u00D1"

    #define Q  "\u00BF"

    /*
     * Caracter unicode en forma de punto que solo puede usarse 
     * en las consolas graficas (Por defecto el programa solo
     * lo usa en los unix).
     */
    #define PUNTO "\u25CF"

#endif // Fin _WIN32

#endif // Fin _ACENTOS_H
