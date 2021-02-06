all: Przetwarzanie_obrazów_2_funkcje.o Przetwarzanie_obrazów_2.o
	gcc -std=c99 -pedantic -Wall Przetwarzanie_obrazów_2_funkcje.o Przetwarzanie_obrazów_2.o -o Przetwarzanie_Obrazów.out
	-rm -f *.o 
Przetwarzanie_obrazów_2_funkcje.o: Przetwarzanie_obrazów_2_funkcje.o Przetwarzanie_obrazów_2.h
	gcc Przetwarzanie_obrazów_2_funkcje.c -c -o Przetwarzanie_obrazów_2_funkcje.o
Przetwarzanie_obrazów_2.o: Przetwarzanie_obrazów_2.o Przetwarzanie_obrazów_2.h
	gcc Przetwarzanie_obrazów_2.c -c -o Przetwarzanie_obrazów_2.o



