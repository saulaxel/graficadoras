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

#define DEBUG

#ifdef __unix__
    #include "../funciones.h"
    #include "../acentos.h"
#else // Windows
    #include "..\funciones.h"
    #include "..\acentos.h"
#endif

#include "graficadora.h"

/*==============*
 * Definiciones *
 *==============*/
#define SALIR    0

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
    bool graficar_una_vez = false;

    if( argc != 3 ) {
        desplegarInstrucciones();
        exit(EXIT_SUCCESS);
    }

    if( !establecerTamanioPanel(argv + 1) ) {
        // Salir del programa si no se pudo asignar memoria
        imprimirError("Tama" N "o de pantalla incorrecto\n");
    }

    do {
        opcion = menu();
#ifdef DEBUG
            printf("Saliendo del menU\n");
            printf("opciOn = %hd\n", opcion);
#endif // DEBUG

        if( opcion == 100 ) {
            graficar_una_vez = true;
        } else if( opcion != 0) {
            pintarEjes();

            (*PEDIR_DATOS_FUNC[opcion - 1])();

            pintarFuncion(FUNCION[opcion - 1]);

            graficar();

#ifdef DEBUG
            printf("DespuEs de graficar\n");
#endif // DEBUG

            if(graficar_una_vez) {
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
    puts("como argumentos las dimensiones en l" I "neas y");
    puts("y en columnas de tu consola.");

    return;
}

/* ================================================= *
 * FunciOn    : menu                                 *
 * DescripciOn: Despliega las opciOnes para graficar *
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
                || opcion == 100);
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
