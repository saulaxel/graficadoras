#!/bin/bash

TAMANIO_X=$(tput cols)
TAMANIO_Y=$(tput lines)

echo $#

EJEMPLO[1]='ejemplos/circulo.txt'
EJEMPLO[2]='ejemplos/elipse_alta.txt'
EJEMPLO[3]='ejemplos/elipse_acostada.txt'
EJEMPLO[4]='ejemplos/exponencial.txt'
EJEMPLO[5]='ejemplos/logaritmo.txt'
EJEMPLO[6]='ejemplos/parabola.txt'
EJEMPLO[7]='ejemplos/recta.txt'
EJEMPLO[8]='ejemplos/hiperbola_horizontal.txt'
EJEMPLO[9]='ejemplos/hiperbola_vertical.txt'

if [ $# -eq 1 ]; then
    let a=$1+0
    if [ $a -ne 0 ]; then
        eval "./graficadora_texto_plano.exe $TAMANIO_X $TAMANIO_Y < ${EJEMPLO[$a]}"
    fi
else
    ./graficadora_texto_plano.exe $TAMANIO_X $TAMANIO_Y
fi
