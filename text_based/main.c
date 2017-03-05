/* ====================================================== *
 * Programa: Graficadora basada en texto.                 *
 * DescripciOn: Programa que pregunta al usuario que      *
 *              funciOn graficar y pide los datos         *
 *              concernientes. Las graficas se despliegan *
 *              unicamente usando texto.                  *
 * ====================================================== */

/*========================*
 * Bibliotecas requeridas *
 *========================*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#define NDEBUG

#ifdef __unix__
    #include "../funciones.h"
    #include "../acentos.h"
#else // Windows
    #include "..\funciones.h"
    #include "..\acentos.h"
#endif // Fin __unix__

#include "graficadora.h"

/*==============*
 * Definiciones *
 *==============*/
#define SALIR_TRAS_GRAFICAR 100
#define SALIR               0

/*===========*
 * Funciones *
 *===========*/

void desplegarInstrucciones(void);               // Imprime instrucciones
int8_t menu(void);                               // Imprime opciones y regresa la elecciOn del usuario
void pedirDatos(void);                           // Pregunta el tipo de grAfica y los datos necesarios

// Termina la ejecuciOn tras un mensaje
void imprimirError(const char *mensaje);

/*===================*
 * FunciOn principal *
 *===================*/
int32_t main(int32_t argc, char **argv){
    int8_t opcion;
    bool interrumpir = false;

    if( argc != 3 ) {
        desplegarInstrucciones();
        exit(EXIT_FAILURE);
    }

    if( !establecerTamanioPanel(argv + 1) ) {
        // Salir del programa si no se pudo asignar memoria
        imprimirError("Tama" N "o de pantalla incorrecto\n");
    }

    do {
        opcion = menu();
#ifndef NDEBUG
            printf("Saliendo del menU\n");
            printf("opciOn = %hd\n", opcion);
#endif // NDEBUG

        if( opcion == SALIR_TRAS_GRAFICAR ) {
            interrumpir = true;
        } else if( opcion != 0) {
            pintarEjes();

            (*PEDIR_DATOS_FUNC[opcion - 1])();

            pintarFuncion(FUNCION[opcion - 1]);

            graficar();

#ifndef NDEBUG
            printf("DespuEs de graficar\n");
            printf("Se grafico la funciOn %s\n", DESC_FUNC[opcion -1]);
#endif // NDEBUG

            if( interrumpir ) {
                // OpciOn especial para cuando la entrada es un archivo
                // y queremos que solo haga una demostraciOn rApida.
                break;
            }

        } else {
            printf("Gracias por usar nuestra aplicaci" O "n, vuelva pronto\n");
        }

    } while( opcion != SALIR );

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
    puts("como argumentos las dimensiones de tu consola.");
    puts("El primer argumento son las columnas y el");
    puts("segundo son las filas.");

    return;
}

/* ================================================= *
 * FunciOn    : menu                                 *
 * DescripciOn: Despliega las opciones para graficar *
 *              y pide el resultado al usuario.      *
 * Regresa    : Entero correspondiente a la opciOn  *
 *              seleccionada                         *
 * ================================================= */
int8_t menu(void) {
    int16_t opcion;
    bool opcionValida = false;

    system(CLEAR);

    printf(".-\"-.     .-\"-.     .-\"-.     .-\"-.     .-\"-.     \n");
    printf("     \"-.-\"     \"-.-\"     \"-.-\"     \"-.-\"     \"-.-\"\n\n");

    puts("Elige la funci" O "n que quieres graficar");
    printf("\n-------------------------------------------------\n");
    for(int i = 0; i < NUM_FUNCIONES; i++) {
        printf("%8s%2d ) %-40s\n",
                "", i + 1, DESC_FUNC[i]);
    }
    printf("%24s%25s\n", "", "+-----------------------+");
    printf("%24s%25s\n", "", "| Preciona 0 para salir |");
    printf("%24s%25s\n", "", "+-----------------------+");

    printf("\n     .-\"-.     .-\"-.     .-\"-.     .-\"-.     .-\"-.     \n");
    printf("\"-.-\"     \"-.-\"     \"-.-\"     \"-.-\"     \"-.-\"\n");

    while( !opcionValida ) {
        char c;
        printf(" > ");
        opcionValida = scanf("%hd", &opcion) 
            && ( ( opcion >= 0 && opcion <= NUM_FUNCIONES )
                    || opcion == SALIR_TRAS_GRAFICAR );
        while( (c = getchar()) != '\n' && c != EOF );
    }

    return (int8_t)opcion;
}

/*===============================================*
 * FunciOn    : imprimirError                    *
 * DescripciOn: Imprime un error y luego termina *
 *              la ejecuciOn.
 * Regresa    : nada                             *
 *===============================================*/
void imprimirError(const char * mensaje) {
    fprintf(stderr, "%s", mensaje);

    exit(EXIT_FAILURE);
}
