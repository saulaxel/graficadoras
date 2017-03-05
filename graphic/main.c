#define GRAFICAR_CON_SDL
#include "graficadora.h"

int * sumaSeniales(float x) {
    static int y[2] = {1};

    y[1] = 100 * ( ( 4  ) * sin(x / 512)
            - ( 2  ) * sin(x / 256)
            - ( 1  ) * sin(x / 128)
            - (0.5) * sin(x / 64)
            + (.25) * sin(x / 32)
            - (.12) * sin(x / 16)
            + (.06) * sin(x / 8)
            );

    return y;

}

int * multSeniales(float x) {
    static int y[2] = {1};

    y[1] = 200 * (
                 ( 1 ) * sin(x / 32)
               * ( 1 ) * sin(x / 16)
               * ( 1 ) * sin(x / 8)
               );

    return y;

}

int * nose(float x) {
    static int y[2] = {1};

    int b = (x > 0)? 1 : -1;

    y[1] = ( (int)x / 100  ) % 2 == 0 ? 100 * b: -100 * b;

    return y;

}

int * tangente(float x) {
    static int y[2] = {1};

    x /= 50;

    y[1] = tan(x);

    return y;

}

int * cubica(float x) {
    static int y[2] = {1};
    x /= 50;

    y[1] = x * x * x;

    return y;

}

int main(void) {
    abrirGraficadora();

    /*pintarFuncion(sumaSeniales);*/
    /*pintarFuncion(multSeniales);*/
    /*pintarFuncion(cubica);*/
    /*pintarFuncion(nose);*/
    /*pintarFuncion(multSeniales);*/
    /*pintarFuncion(tangente);*/

    getchar();
    cerrarGraficadora();
    return 0;

}
