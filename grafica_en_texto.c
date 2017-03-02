/* ====================================================== *
 * Programa: Graficadora basada en texto.                 *
 * DescripciOn: Programa que pregunta al usuario que      *
 *              funciOn graficar y pide los datos         *
 *              concernientes. Las graficas se despliegan *
 *              unicamente usando texto.                  *
 * ====================================================== */

/*=======================*
 * Bibliotecas incluidas *
 *=======================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

/*==============*
 * Definiciones *
 *==============*/
#define ESCALA 2

#ifdef _WIN32
    #define CLEAR "cls"
    #define A "\xA0"
    #define E "\x82"
    #define I "\xA1"
    #define O "\xA2"
    #define U "\xA3"
    #define N "\xA4"
#else // unix
    #define CLEAR "clear"
    #define A "\u00E1"
    #define E "\u00E9"
    #define I "\u00ED"
    #define O "\u00F3"
    #define U "\u00FA"
    #define N "\u00F1"
    #define PUNTO "\u25CF"
#endif // Fin _WIN32

#define SALIR 0
#define GRAFICAS 5

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
void establecerTamanioPanel(char **);    // Asigna tamanio dinAmicamente
void eliminaPanel(void);                 // Libera la memoria
void pintarEjes(void);                   // Pone carActeres en la matriz para representar los ejes
void pintarFuncion(void);                // Establece puntos en la matriz
void graficar(void);                     // Imprime la matriz a pantalla

int funcion(double x);                  // Funcion a graficar

void desplegarInstrucciones(void);       // Imprime instrucciones
int8_t menu(void);                             // Imprime opciones y regresa la elecciOn del usuario
void pedirDatos(void);                   // Pregunta el tipo de grAfica y los datos necesarios

// Termina la ejecuciOn tras un mensaje
void imprimirError(const char *mensaje);

/*===================*
 * FunciOn principal *
 *===================*/
int32_t main(int32_t argc, char **argv){
    int8_t opcion;
    if( argc != 3 ) {
        desplegarInstrucciones();
        exit(EXIT_SUCCESS);
    }

    establecerTamanioPanel(argv + 1);

    do {
        opcion = menu();
    } while( opcion != SALIR );

    pintarEjes();
    pintarFuncion();

    graficar();

    return EXIT_SUCCESS;
}

/* ================================================ *
 * FunciOn    : desplegarInstrucciones              *
 * DescripciOn: Despliega la forma en que deben ser *
 *              usados los argumentos               *
 * ================================================ */
void desplegarInstrucciones(void) {
    puts("Graficadora en texto plano:");
    puts("\nEl programa requiere que se le indique");
    puts("romo argumentos las dimensiones en l" I "neas y");
    puts("y en columnas de tu consola.");

    return;
}

/* ================================================= *
 * FunciOn    : menU                                 *
 * DescripciOn: Despliega las opciOnes para graficar *
 *              y pide el resultado al usuario.      *
 * Regresa    :  entero correspondiente a la opciOn  *
 *              seleccionada                         *
 * ================================================= */
int8_t menu(void) {
    int16_t opcion;
    bool opcionValida = false;

    puts("Elige lo que quieres graficar");
    puts("\t1 ) Polinomica(Max grado 3).");
    puts("\t2 ) Eliptica.");
    puts("\t3 ) Hiperbolica.");
    puts("\t4 ) Trigonometrica.");
    puts("\t5 ) Exponencial / Logaritmica.");

    while( !opcionValida ) {
        int c;
        printf("> ");
        opcionValida = scanf("%hd", &opcion) 
            && opcion > 0 && opcion < GRAFICAS;
        do {
            c = getchar();
        } while( c != '\n' && c != EOF );
    }

    return (int8_t)opcion;
}

/* ====================================================== *
 * FunciOn    : establecerTamanioPanel                    *
 * DescripciOn: Verifica si los argumentos recibidos      *
 *              por lInea de comandos son enteros validos *
 *              y termina la ejecuciOn en caso de que no  *
 * ====================================================== */
void establecerTamanioPanel(char **tamanio) {
    if( (TAM_X = atoi(tamanio[0])) == 0 ||
        (TAM_Y = atoi(tamanio[1])) == 0 
      ) 
    {
        // Salir del programa
        imprimirError("Tama" N "o de pantalla incorrecto\n");
    }

    return;
}

/* ========================================================= *
 * FunciOn     :  pintarEjes                                 *
 * DescripciOn :  Limpia la matriz y pone en ella caracteres *
 *                que se en conjunto se asemejan a un par de *
 *                ejes cartesianos                           *
 * Regresa     :  nada                                       *
 * ========================================================= */
void pintarEjes(void) {
    int n, m;

    // Se limpia la grAfica (por si se quiere reutilizar)
    for(n = 0; n < TAM_X; ++n){
        for(m = 0; m <TAM_Y; ++m){
            panel[n][m] = ' ';
        }
    }

    // Eje x
    for(n = 0; n < TAM_X; ++n){
        panel[n][TAM_Y / 2 - 1] = '-';
    }

    // Eje y
    for(n = 0; n < TAM_Y; ++n){
        panel[TAM_X / 2 -1][n] = '|';
    }

    // Origen
    panel[TAM_X / 2 - 1][TAM_Y / 2 - 1] = '+';

    return;
}

int funcion(double x) {
    if( x == 0 ){
        return 50;
    }

    return 500 * sin(x/10)/x;
}

void pintarFuncion() {
    int i, juno, jdos;
    for(i = 0; i < TAM_X; ++i){
        juno =  funcion((float)(i - TAM_X / 2 + 1) / ESCALA) + TAM_Y / 2 - 1;
        jdos = -funcion((float)(i - TAM_X / 2 + 1) / ESCALA) + TAM_Y / 2 - 1;
        if( juno >= 0 && juno < TAM_Y ){
            panel[i][juno] = '*';
        }
        if( jdos >= 0 && jdos < TAM_Y ){
            panel[i][jdos] = '*';
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

    return;
}

void imprimirError(const char * mensaje) {
    fprintf(stderr, "%s", mensaje);

    exit(EXIT_FAILURE);
}
