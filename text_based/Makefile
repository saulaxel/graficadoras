# No tengo la menor idea de como hacer un Makefile :S

# Compilador
CC = gcc
# Banderas
CFLAGS = -std=c99 -lm
# Dependencias
DEPS = ../acentos.h ../funciones.h graficadora.h

graficadora_texto_plano.exe: main.o
	$(CC) -o graficadora_texto_plano.exe main.o $(CFLAGS)

main.o: main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
