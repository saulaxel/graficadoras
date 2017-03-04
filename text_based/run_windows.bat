echo off

SET TAMANIO_X=140
SET TAMANIO_Y=70

mode con:cols=%TAMANIO_X% lines=%TAMANIO_Y%

set argc=0
for %%x in (%*) do set /a argc+=1 

EJEMPLO[!1!]='ejemplos\circulo.txt'
EJEMPLO[!2!]='ejemplos\elipse_alta.txt'
EJEMPLO[!3!]='ejemplos\elipse_acostada.txt'
EJEMPLO[!4!]='ejemplos\exponencial.txt'
EJEMPLO[!5!]='ejemplos\logaritmo.txt'
EJEMPLO[!6!]='ejemplos\parabola.txt'
EJEMPLO[!7!]='ejemplos\recta.txt'
EJEMPLO[!8!]='ejemplos\hiperbola_horizontal.txt'
EJEMPLO[!9!]='ejemplos\hiperbola_vertical.txt'

if %argc% == 0 goto sin_ejemplo
if %argc% == 1 goto con_ejemplo

:sin_ejemplo
    .\graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y%

exit /b 0

:con_ejemplo

COMANDO=".\graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < !EJEMPLO[%a]}"

%COMANDO%
exit /b 0
