@echo off

:: Tamanio estandar
::SET TAMANIO_X=80
::SET TAMANIO_X=23

:: Tamanio personalizado 1
::SET TAMANIO_X=84
"SET TAMANIO_Y=43

:: Tamanio personalizado 2
::SET TAMANIO_X=257
::SET TAMANIO_Y=110

set argc=0
for %%x in (%*) do set /a argc+=1 

set ejemplo1=ejemplos\circulo.txt
set ejemplo2=ejemplos\elipse_alta.txt
set ejemplo3=ejemplos\elipse_acostada.txt
set ejemplo4=ejemplos\exponencial.txt
set ejemplo5=ejemplos\logaritmo.txt
set ejemplo6=ejemplos\parabola.txt
set ejemplo7=ejemplos\recta.txt
set ejemplo8=ejemplos\hiperbola_horizontal.txt
set ejemplo9=ejemplos\hiperbola_vertical.txt

if %argc% == 0 goto sin_ejemplo
if %argc% == 1 goto con_ejemplo

:sin_ejemplo

graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y%

exit /b 0

:con_ejemplo

if %1 == 1 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo1%
if %1 == 2 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo2%
if %1 == 3 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo3%
if %1 == 4 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo4%
if %1 == 5 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo5%
if %1 == 6 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo6%
if %1 == 7 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo7%
if %1 == 8 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo8%
if %1 == 9 graficadora_texto_plano.exe %TAMANIO_X% %TAMANIO_Y% < %ejemplo9%

exit /b 0
