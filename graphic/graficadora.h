#ifndef _GRAFICADORA_H
#define _GRAFICADORA_H

#ifdef GRAFICAR_CON_OPENGL
    #include <GL/glut.h>
#elif defined(GRAFICAR_CON_SDL)
    #include <graphics.h>
#endif

#include <math.h>

#define TAMX 640
#define TAMY 480

#define TAMFLECHA 20

#define ESPACIO 10

void pintarEjes(void);


#ifdef GRAFICAR_CON_SDL

int * (*f)(float x);

void abrirGraficadora(void) {
    int gd = DETECT, gm;

    initgraph(&gd, &gm, NULL);

    pintarEjes();

#elif defined(GRAFICAR_CON_OPENGL)
void abrirGraficadora(int argc, char**argv) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutInit(&argc, &argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(TAMX, TAMY);

    glutCreateWindow("Graficadora UNAM");
    glutDisplayFunc(display);

#endif

    return;
}

#ifdef GRAFICAR_CON_OPENGL
void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);

    pintarEjes();

    pintarFuncion(f);

    glFlush();
}
#endif


#ifdef GRAFICAR_CON_SDL
void cerrarGraficadora(void) {
    closegraph();

    return;

}
#elif defined(GRAFICAR_CON_OPENGL)
void elegirFuncion(int * (*func)(float)) {
    f = func;
    return;
}
#endif

void pintarEjes(void) {
#ifdef GRAFICAR_CON_SDL
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
#elif defined(GRAFICAR_CON_OPENGL)

    glBegin(GL_LINES);
    /*glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(10, 0, 0);*/
    /*glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 10, 0);*/
    /*glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 10);*/

    glColor3f(1, 1, 1);
    glVertex2d(0, 0);
    glVertex2d(0.1,0.1);
    glEnd();

#endif

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
#ifdef GRAFICAR_CON_SDL
                line(
                        x - 1,
                        -y_ant[i] + TAMY / 2,
                        x,
                        -y_act[i] + TAMY / 2

                    );
#elif defined(GRAFICAR_CON_OPENGL)
#endif

            }
            for(int s = 0; s <= y_act[0]; s++) {
                y_ant[s] = y_act[s];

            }

        }

    }

#ifdef GRAFICAR_CON_OPENGL
    glutMainLoop();
#endif // GRAFICAR_CON_OPENGL

    free(y_ant);
}

#endif // _GRAFICADORA_H
