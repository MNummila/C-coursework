HT: paaohjelma.o nimilista.o tuloslista.o
	gcc paaohjelma.o nimilista.o tuloslista.o -o HT -lm
paaohjelma.o: paaohjelma.c nimilista.h tuloslista.h
	gcc paaohjelma.c -c -lm
nimilista.o: nimilista.c nimilista.h tuloslista.h
	gcc nimilista.c -c -lm
tuloslista.o: tuloslista.c nimilista.h tuloslista.h
	gcc tuloslista.c -c -lm
