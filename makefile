all: Przetwarzanie_obrazów_2_funkcje.o Przetwarzanie_obrazów_2.o image_processing_wrote_load.o
	gcc -std=c99 -pedantic -Wall Przetwarzanie_obrazów_2_funkcje.o Przetwarzanie_obrazów_2.o image_processing_wrote_load.o -o Przetwarzanie_Obrazów.out
	-rm -f *.o 
Przetwarzanie_obrazów_2_funkcje.o: Przetwarzanie_obrazów_2_funkcje.o Przetwarzanie_obrazów_2.h
	gcc Przetwarzanie_obrazów_2_funkcje.c -c -o Przetwarzanie_obrazów_2_funkcje.o
Przetwarzanie_obrazów_2.o: Przetwarzanie_obrazów_2.o Przetwarzanie_obrazów_2.h
	gcc Przetwarzanie_obrazów_2.c -c -o Przetwarzanie_obrazów_2.o
image_processing_wrote_load.o: image_processing_wrote_load.o Przetwarzanie_obrazów_2.h
	gcc image_processing_wrote_load.c -c -o image_processing_wrote_load.o



