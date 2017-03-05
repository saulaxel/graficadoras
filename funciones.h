
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

#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include "acentos.h"

/*=======================================*
 * Definiciones de macros y de variables *
 *=======================================*/

#define NUM_FUNCIONES 10

#define PI  3.1415926535
#define EXP  2.7182818284

const char * const DESC_FUNC[NUM_FUNCIONES] = {
    "Lineal"                              , // 1
    "Polin" O "mica (M" A "ximo grado 3)" , // 2
    "Circulo"                             , // 3
    "El" I "ptica"                        , // 4
    "Hiperb" O "lica"                     , // 5
    "Seno"                                , // 6
    "Coseno"                              , // 7
    "Tangente"                            , // 8
    "Exponencial"                         , // 9
    "Logaritmica"                           // 10
};

/*-* Funciones a graficar *-*/

int16_t * func_polinomica(double f, bool init_values, ...);
int16_t * func_conica_cuad(double f, bool init_values, ...);
int16_t * func_sin(double f, bool init_values, ...);
int16_t * func_tan(double f, bool init_values, ...);
int16_t * func_exponencial(double f, bool init_values, ...);
int16_t * func_logaritmo(double f, bool init_values, ...);

/*-* Funciones que validan los datos *-*/
void datos_recta(void);
void datos_polinomica(void);
void datos_circulo(void);
void datos_elipse(void);
void datos_hiperbola(void);
void datos_seno(void);
void datos_coseno(void);
void datos_senoidal(bool coseno);
void datos_tangente(void);
void datos_exponencial(void);
void datos_logaritmo(void);

// Arreglo que contiene a las funciones que piden datos y llaman a 
// las funciones
void (* const PEDIR_DATOS_FUNC[NUM_FUNCIONES])(void) = {
    &datos_recta       , // 1
    &datos_polinomica  , // 2
    &datos_circulo     , // 3
    &datos_elipse      , // 4
    &datos_hiperbola   , // 5
    &datos_seno        , // 6
    &datos_coseno      , // 7
    &datos_tangente    , // 8
    &datos_exponencial , // 9
    &datos_logaritmo     // 10
};

// Arreglo que contiene las funciones a las que hay que llamar
int16_t * (* const FUNCION[NUM_FUNCIONES]) (double, bool, ...) = {
    &func_polinomica  , // 1
    &func_polinomica  , // 2
    &func_conica_cuad , // 3
    &func_conica_cuad , // 4
    &func_conica_cuad , // 5
    &func_sin         , // 6
    &func_sin         , // 7
    &func_tan         , // 8
    &func_exponencial , // 9
    &func_logaritmo     // 10
};

double leerDoble(double min, double max);

/*===================*
 * SecciOn de cOdigo *
 *===================*/

//#################################################################
// Nota : Todas las funciones tienen en comUn el hecho de recibir
//        un booleano así como un número variable de argumentos
//        por la misma razón: siempre que el booleano sea 'true' 
//        se evaluaran los argumentos de la lista para inicializar
//        los datos de la función en particular (ej: los ejes de 
//        la hiperbola) los cuales se guardaran en datos
//        estAticos. DespuEXPs de la primera llamada a la funciOn
//        las llamadas posteriores deberAn ser invocadas con false
//        y sin los argumentos extras para preservar los datos 
//        previos.
//#################################################################

// Se desabilitan los warnings por los argumentos variables
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wvarargs"

/*
 * Funcion     : func_polinomica
 * DescripciOn : Calcula los valores de las ordenadas de una 
 *               funciOn polinomica dada.
 *
 * Regresa     : EXPl valor de la ordenada de la funcion.
 */
int16_t * func_polinomica(double x, bool init_values, ...) {
    // Areglo para los coeficientes del polinomio
    // de la forma a0*x^0 + a1*x^1 + a2*x^2 + a3*x^3
    static double coeficientes[4] = { 0 };
    static double desp_x, desp_y;
    static int16_t y[2] = { 0 };

    if( init_values ) {
        va_list apt_args;
        va_start(apt_args, 6); /* La lista de argumentos variables */
                               /* debe corresponder con los 4 coeficientes */
                               /* mAs los dos desplazamientos */

        for(int i = 0; i < 4; i++) {
            coeficientes[i] = va_arg(apt_args, double);
        }

        desp_x = va_arg(apt_args, double);
        desp_y = va_arg(apt_args, double);

#ifndef NDEBUG
        printf("Los valores son: \n");
        printf("a0 = %lf a1 = %lf a2 = %lf a3 = %lf\n",
                coeficientes[0], coeficientes[1],
                coeficientes[2], coeficientes[3]);
        printf("desplazamiento x = %lf desplazamineto y = %lf\n", desp_x, desp_y);
#endif

        va_end(apt_args);

        y[0] = 1; // RegresarA 1 valor cada vez que sea llamada

    } else {
        x -= desp_x;

        y[1] = coeficientes[0] +            // x^0
               coeficientes[1] * x +        // x^1
               coeficientes[2] * x * x +    // x^2
               coeficientes[3] * x * x * x; // x^3

        y[1] += desp_y;
#ifndef NDEBUG
        printf("El valor de y es: %hd\n", y[1]);
#endif
    }
    return y;
}

/*
 * Funcion     : func_conica_cuad
 * DescripciOn : Calcula los valores de las ordenadas de una
 *               funciOn eliptica o hiperbolica dada.
 *
 * Regresa     : Los valores de la ordenada de la elipse o 
 *               hiperbola.
 */
int16_t * func_conica_cuad(double x, bool init_values, ...) {
    // Areglo para los coeficientes del polinomio
    // de la forma a0*x^0 + a1*x^1 + a2*x^2 + a3*x^3
    static double eje_x, eje_y;
    static double desp_x, desp_y;
    static int tipo; // false para elipse, true para hiperbola

    static int16_t y[3] = { 0 };

    if( init_values ) {
        va_list apt_args;
        va_start(apt_args, 5); /* La lista de argumentos variables */
        /* debe corresponder con los tamanios de los dos ejes coeficientes */

        eje_x = va_arg(apt_args, double);
        eje_y = va_arg(apt_args, double);

        desp_x = va_arg(apt_args, double);
        desp_y = va_arg(apt_args, double);

        tipo = va_arg(apt_args, int);

#ifndef NDEBUG
        printf("Los valores son:\n");
        printf("largo x: %lf largo y: %lf\n", eje_x, eje_y);
        printf("desplazamineto x %lf desplazamineto y %lf\n",
                desp_x, desp_y);
#endif

        va_end(apt_args);

        y[0] = 2; // RegresarA 2 valores cada vez que sea llamada

    } else {
        x -= desp_x;

        double arg;

        // Los signos se declaran enteros de 16 bits
        // para evitar que se hagan parseos de mAs al
        // hacer operaciones.
        int8_t signo1 = (tipo & 1) ? -1 : 1;
        int8_t signo2 = (tipo & 2) ? -1 : 1;

#ifndef NDEBUG
        printf("Los signos son: signo1 = %hd signo2 = %hd\n",
                (short)signo1, (short)signo2);
#endif

        arg = signo2 * (eje_x*eje_x + signo1 * x*x);

        if( arg >= 0 ) {
            y[1] = eje_y * sqrt(arg) / eje_x;
        } else {
            y[1] = 10000;
        }
        y[2] = -y[1];

        y[1] += desp_y;
        y[2] += desp_y;

#ifndef NDEBUG
        printf("Los valores de y son\n");
        printf("y1 = %hd y2 = %hd\n", y[1], y[2]);
#endif
    }

    return y;
}

/*
 * Funcion     : func_sin
 * DescripciOn : Calcula los valores de las ordenadas de una 
 *               funciOn senoidal dada.
 *
 * Regresa     : EXPl valor de la ordenada de la senoidal.
 */
int16_t * func_sin(double x, bool init_values, ...) {
    // Una senoidal del tipo amplitud sin(x / periodo)
    // ( EXPn realidad es x / periodo / 2 * pi pero eso complica
    // las cosas )
    static double amplitud, periodo;
    static double desp_x, desp_y;

    static int16_t y[2] = { 0 };

    if( init_values ) {
        va_list apt_args;
        va_start(apt_args, 4); // Amplitud, periodo y dos
                               // desplazamientos

        amplitud = va_arg(apt_args, double);
        periodo = va_arg(apt_args, double);

        desp_x = va_arg(apt_args, double);
        desp_y = va_arg(apt_args, double);

#ifndef NDEBUG
        printf("Los valores recibidos son:\n");
        printf("amplitud = %lf periodo = %lf\n", amplitud, periodo);
        printf("desplazamienot x = %lf desplazamiento y = %lf\n",
                desp_x, desp_y);
#endif

        va_end(apt_args);

        y[0] = 1; // RegresarA 1 valores cada vez que sea llamada

    } else {
        x -= desp_x;

        y[1] = amplitud * sin( x / periodo );

        y[1] += desp_y;

#ifndef NDEBUG
        printf("El valor de y1 es: %hd\n", y[1]);
#endif
    }

    return y;
}

/*
 * Funcion     : func_tan
 * DescripciOn : Calcula los valores de las ordenadas de una 
 *               funciOn tangente dada.
 *
 * Regresa     : EXPl valor de la ordenada tangente.
 */
int16_t * func_tan(double x, bool init_values, ...) {
    // Similar al seno, la funciOn es de tipo 
    // amplitud * tan( x / periodo )
    static double amplitud, periodo;
    static double desp_x, desp_y;

    static int16_t y[2] = { 0 };

    if( init_values ) {
        va_list apt_args;
        va_start(apt_args, 4); // Amplitud, periodo y dos
                               // desplazamientos

        amplitud = va_arg(apt_args, double);
        periodo = va_arg(apt_args, double);

        desp_x = va_arg(apt_args, double);
        desp_y = va_arg(apt_args, double);

#ifndef NDEBUG
        printf("Los valores recibidos son:\n");
        printf("amplitud = %lf periodo = %lf\n", amplitud, periodo);
        printf("desplazamienot x = %lf desplazamiento y = %lf\n",
                desp_x, desp_y);
#endif

        va_end(apt_args);

        y[0] = 1; // RegresarA 1 valores cada vez que sea llamada

    } else {
        x -= desp_x;

        y[1] = amplitud * tan( x / periodo );

        y[1] += desp_y;

#ifndef NDEBUG
        printf("El valor de y1 es: %hd\n", y[1]);
#endif
    }

    return y;
}

/*
 * Funcion     : func_exponencial
 * DescripciOn : Calcula los valores de las ordenadas de una 
 *               funciOn exponencial dada.
 *
 * Regresa     : EXPl valor de la ordenada de la exponencial.
 */
int16_t * func_exponencial(double x, bool init_values, ...) {
    // FunciOn exponencial de tipo
    // a0 * e^(x / b)
    static double a, b;
    static double desp_x, desp_y;

    static int16_t y[2] = { 0 };

    if( init_values ) {
        va_list apt_args;
        va_start(apt_args, 4); // a, b y desplazamientos

        a = va_arg(apt_args, double);
        b = va_arg(apt_args, double);

        desp_x = va_arg(apt_args, double);
        desp_y = va_arg(apt_args, double);

#ifndef NDEBUG
        printf("Los datos son:\n");
        printf("a = %lf b = %lf\n", a, b);
        printf("desp x = %lf desp y = %lf\n", desp_x, desp_y);
        getchar();
#endif

        va_end(apt_args);

        y[0] = 1; // RegresarA 1 valores cada vez que sea llamada

    } else {
        x -= desp_x;

        y[1] = a * pow(EXP, x / b);

        y[1] += desp_y;

#ifndef NDEBUG
        printf("El valor de y[1] es: %hd\n", y[1]);
#endif
    }

    return y;
}

/*
 * Funcion     : func_logaritmo
 * DescripciOn : Calcula los valores de las ordenadas de una 
 *               funciOn logaritnica dada.
 *
 * Regresa     : El valor de la ordenada de la logaritmica.
 */
int16_t * func_logaritmo(double x, bool init_values, ...) {
    // FunciOn logaritmica de tipo a * ln( b * x )
    static double a, b;
    static double desp_x, desp_y;

    static int16_t y[2] = { 0 };

    if( init_values ) {
        va_list apt_args;
        va_start(apt_args, 4); // a, b y desplazamientos

        a = va_arg(apt_args, double);
        b = va_arg(apt_args, double);

        desp_x = va_arg(apt_args, double);
        desp_y = va_arg(apt_args, double);

#ifndef NDEBUG
        printf("Los datos son:\n");
        printf("a = %lf b = %lf\n", a, b);
        printf("desp x = %lf desp y = %lf\n", desp_x, desp_y);
        getchar();
#endif

        va_end(apt_args);

        y[0] = 1; // RegresarA 1 valores cada vez que sea llamada

    } else {
        x -= desp_x;
        double arg = x * b;

        y[1] = (arg > 0) ? a * log(x * b) : 10000;

        y[1] += desp_y;

#ifndef NDEBUG
        printf("El valor de y1 es: %hd\n", y[1]);
#endif
    }

    return y;
}

// Se reabilitan los warnings
#pragma GCC diagnostic pop

/*-* Funciones que piden datos *-*/
void datos_recta(void) {
    double m, b;

    printf("Ingresa la pendiente de la recta (-100 a 100)\n");
    m = leerDoble(-100.01, 100.01);

    printf("Ingresa la ordenada de la recta (-100 a 100)\n");
    b = leerDoble(-100.01, 100.01);

    func_polinomica(0.0, true, b, m, 0.0, 0.0, 0.0, 0.0);

    return;
}

void datos_polinomica(void) {
    int grado;
    double a[4] = {0};
    double desp_x, desp_y;

    printf("Ingrese el grado de la ecuaci" O "n (0  a 3)\n");
    grado = (int) leerDoble(-0.01, 3.01);

    for(int i = 0; i <= grado; i++) {
        printf("Ingrese el coeficiente a%d(-100 a 100)\n", i);
        a[i] = leerDoble(-100.01, 100.01);
    }

    printf("Ingrese el desplazamiento en x (-200 a 200)\n");
    desp_x = leerDoble(-200.01, 200.01);

    printf("Ingrese el desplazamiento en y (-200 a 200)\n");
    desp_y = leerDoble(-200.01, 200.01);

    func_polinomica(0.0, true, a[0], a[1], a[2], a[3], desp_x, desp_y);

    return;
}

void datos_circulo(void) {
    double radio;
    double desp_x, desp_y;

    printf("Ingrese el radio del circulo (0 a 100)\n");
    radio = leerDoble(0.0, 100.01);

    printf("Ingrese el desplazamiento en x (-200 a 200)\n");
    desp_x = leerDoble(-200.01, 200.01);

    printf("Ingrese el desplazamiento en y (-200 a 200)\n");
    desp_y = leerDoble(-200.01, 200.01);

    func_conica_cuad(0.0, true, radio, radio, desp_x, desp_y, 1);

    return;
}

void datos_elipse(void) {
    double eje_x, eje_y;
    double desp_x, desp_y;

    printf("Ingrese el tama" N "o del semieje x (0 a 100)\n");
    eje_x = leerDoble(0.0, 100.01);

    printf("Ingrese el tama" N "o del semieje y (0 a 100)\n");
    eje_y = leerDoble(0.0, 100.01);

    printf("Ingrese el desplazamiento en x (-200 a 200)\n");
    desp_x = leerDoble(-200.01, 200.01);

    printf("Ingrese el desplazamiento en y (-200 a 200)\n");
    desp_y = leerDoble(-200.01, 200.01);

    func_conica_cuad(0.0, true, eje_x, eje_y, desp_x, desp_y, 1);

    return;
}

void datos_hiperbola(void) {
    int8_t orientacion;
    double tam_x, tam_y;
    double desp_x, desp_y;

    printf(Q "Hiperbola horizontal o vertical?"
            " (1 para horizontal/ 2 para vertical)\n");

    orientacion = (int8_t) leerDoble(0.99, 2.01);

    orientacion = (orientacion == 1) ? 0 : 3;

    printf("Ingrese el tama" N "o del eje x (-100, 100)\n");
    tam_x = leerDoble(-100.01, 100.01);

    printf("Ingrese el tama" N "o del eje x (-100, 100)\n");
    tam_y = leerDoble(-100.01, 100.01);

    printf("Ingrese el desplazamiento en x (-200, 200)\n");
    desp_x = leerDoble(-200.01, 200.01);

    printf("Ingrese el desplazamiento en y (-200, 200)\n");
    desp_y = leerDoble(-200.01, 200.01);

    func_conica_cuad(0.0, true, tam_x, tam_y, desp_x, desp_y, orientacion);

    return;
}

void datos_seno(void) {
    datos_senoidal(false);
    return;
}

void datos_coseno(void) {
    datos_senoidal(true);
    return;
}

void datos_senoidal(bool coseno) {
    double amplitud, periodo;
    double desp_x, desp_y;

    printf("Ingresa la amplitud (-100, 100)\n");
    amplitud = leerDoble(-100.01, 100.01);

    printf("Ingresa el periodo (-100, 100)\n");
    periodo = leerDoble(-100.01, 100.01);

    printf("Ingresa el desplazamientos en x (-200, 200)\n");
    desp_x = leerDoble(-200, 200);

    printf("Ingresa el desplazamientos en y (-200, 200)\n");
    desp_y = leerDoble(-200, 200);

    func_sin(0.0, true, amplitud,
            periodo, desp_x - (coseno? amplitud * PI / 2: 0), desp_y);

    return;
}

void datos_tangente(void) {
    double amplitud, periodo;
    double desp_x, desp_y;

    printf("Ingresa la amplitud (-100, 100)\n");
    amplitud = leerDoble(-100.01, 100.01);

    printf("Ingresa el periodo (-100, 100)\n");
    periodo = leerDoble(-100.01, 100.01);

    printf("Ingresa el desplazamientos en x (-200, 200)\n");
    desp_x = leerDoble(-200, 200);

    printf("Ingresa el desplazamientos en y (-200, 200)\n");
    desp_y = leerDoble(-200, 200);

    func_tan(0.0, true, amplitud, periodo, desp_x , desp_y);

    return;

}

void datos_exponencial(void) {
    double a, b;
    double desp_x, desp_y;

    printf("Exponencial de forma a * e^(x / b)\n");
    printf("Ingresa a (-100, 100)\n");
    a = leerDoble(-100.01, 100.01);

    printf("Ingresa b (-100000, 100000)\n");
    b = leerDoble(-100000.01, 100000.01);

    printf("Ingresa los desplazamientos en x (-200, 200)\n");
    desp_x = leerDoble(-200, 200);

    printf("Ingresa los desplazamientos en y (-200, 200)\n");
    desp_y = leerDoble(-200, 200);

    func_exponencial(0.0, true, a, b, desp_x , desp_y);

    return;
}

void datos_logaritmo(void) {
    double a, b;
    double desp_x, desp_y;

    printf("Logaritmica de forma a * ln(x * b)\n");
    printf("Ingresa a (-100, 100)\n");
    a = leerDoble(-100.01, 100.01);

    printf("Ingresa b (-100, 100)\n");
    b = leerDoble(-100.01, 100.01);

    printf("Ingresa los desplazamientos en x (-200, 200)\n");
    desp_x = leerDoble(-200, 200);

    printf("Ingresa los desplazamientos en y (-200, 200)\n");
    desp_y = leerDoble(-200, 200);

    func_logaritmo(0.0, true, a, b, desp_x , desp_y);

    return;

}

double leerDoble(double min, double max) {
    double leido;
    bool valorValido = false;

    while( !valorValido ) {
        char c;
        printf(" > ");
        valorValido = scanf("%lf", &leido) && 
            leido > min && leido < max;

        while( (c = getchar()) != '\n' && c != EOF );
    }

    return leido;
}

#endif // Fin _FUNCIONES_H
