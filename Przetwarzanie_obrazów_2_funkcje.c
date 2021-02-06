#include<stdio.h>
#include <stdlib.h>
#include "Przetwarzanie_obrazów_2.h"

/********************************************************************************************

                       NEGATYW
Funkcja która realizuje przetworzenie obrazu i nak³ada na niego negatyw
PRE:
    Struktura z danymi o obrazie
POST:
     Wykonianie działań na kazdym pikselu obrazu powodujących nalożenie negatywu na obraz
********************************************************************************************/
void Negatyw (T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  int i,j;
  
  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
  
  for (i=0;i<obraz->wymy;i++) {/*Zastosowałem operator warunkowy ponieważ było to chyba najwygodniejszym rozwiazaniem */
    for (j=zm_pom->wybrany_kolor;   j<obraz->format*obraz->wymx;  zm_pom->wybrany_kolor_pom==WYBRANO_KOLOR?j+=3:j++) {
      piksele[i][j]=obraz->szarosci-(piksele[i][j]);
    }
  }
  printf("!!! Wykonano negatyw na obrazie !!! \n\n");
}

/**************************************************************************

                         KONWERSJA DO SZAROSCI
Funkcja, ktora zmienia obraz kolorowy na szary
PRE: 
   Struktura z danymi o obrazie kolorowym, wybór odpowiedniej opcji przez
 użytkownika
POST:
     Wykonanie działań na każdym pikselu obrazu koloroweogo powodujących
 zmiane obrazu kolorowoego w obraz czarno-bialy ( zmiana PPM na PGM).
***************************************************************************/

void konwersja_do_szarosci(T_OBRAZ * obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  int i,j;
  int tymczasowy_obraz[obraz->wymy][obraz->format*obraz->wymx];
  
  /*zmienne pomocnicze do określania pozycji pikseli w naszej tablicy*/
  int z=0;
  int g=1;
  int h=2;

  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;

  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      /*"każdy punkt nowego obrazu jest średnią arytmetyczna wartości składowych kolorów"~cytat z polecenia do zadania*/
      tymczasowy_obraz[i][j]=((piksele[i][j+z]+piksele[i][j+g]+piksele[i][j+h])/3);
      /*W każdym nastepnym kroku petli for dodawane jest 2 do każdej zmiennej */
      z+=2;
      g+=2;
      h+=2;
    }
    /*powrót do stanu początkowego zmiennych w każdym kolejnym wierszu*/
    z=0;
    g=1;
    h=2;
  }
  obraz->format=PGM; // Ustawiamy format na PGM
  zm_pom->wybrany_kolor_pom=0; //Obraz juz nie jest kolorowy
  zm_pom->wybrany_kolor=0; // Obraz nie jest już kolorowy
  free(obraz->piksele);//zwolnienie pamiec zajetej przez tablice z obrazem PPM
  obraz->piksele=malloc(obraz->format*obraz->wymx*obraz->wymy*sizeof(int));// Ponowona alokacja tablicy teraz juz dla obrazu PGM
  
  int (*piksele2)[obraz->format*obraz->wymx];
  piksele2=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
 
  for (i=0;i<obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      piksele2[i][j]=tymczasowy_obraz[i][j];//przypisanie do nowej tablicy zkonwertowanego obrazu 
    }
  }

  printf("!!! Wykonano konwersje obrazu kolorowego na szary !!!\n\n");  
}
/*****************************************************************************

                            OBROT O 90 STOPNI
Funkcja która obraca obrazek o 90 stopni
PRE:
    Struktura z danymi o obrazie
POST:
     Plik z obroconym obrazem o 90 stopni
******************************************************************************/
void Obrot_o_90_stopni(T_OBRAZ * obraz){
  int i,j;
  int temp;
  int obraz_pgm_90[obraz->wymy][obraz->format*obraz->wymx];

  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
  
  /*zamiana wysokosci ( wymy) z szerokoscia (wymx)*/     
  temp=obraz->wymx;
  obraz->wymx=obraz->wymy;
  obraz->wymy=temp;
  
  /*odwrocenie kolumn*/    
  for (i=0;i<obraz->format*obraz->wymy;i++) {
    for (j=0;j<obraz->wymx;j++) {
      obraz_pgm_90[(obraz->format*obraz->wymx)-j-1][i]=piksele[j][i]; 
    }
  }
  free(obraz->piksele); //zwolnienie miejsca dla nowej obrocoenj tablicy
  obraz->piksele=malloc(obraz->format*obraz->wymx*obraz->wymy*sizeof(int));

  /*transpozycja macierzy*/
  if(obraz->format==PGM){//Jeśli obraz PGM
    
    int (*piksele2)[obraz->format*obraz->wymx];
    piksele2=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;

    for (i=0;i<obraz->format*obraz->wymy;i++) {
      for (j=0;j<obraz->wymx;j++) {
	piksele2[i][j]=obraz_pgm_90[j][i];
      }
    }
  }else//Jeśli obraz PPM
    {
      int (*piksele2)[obraz->format*obraz->wymx];
      piksele2=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
      for (i=0;i<obraz->wymy;i++) {
	for (j=0;j<obraz->wymx;j++) {
	  piksele2[i][3*j] = obraz_pgm_90[j][3*i];
	  piksele2[i][(3*j) + 1] = obraz_pgm_90[j][(3*i) + 1];
	  piksele2[i][(3*j) + 2] = obraz_pgm_90[j][(3*i) + 2];
	    }
      }
    }
    
  printf("!!! Wykonano obrot obrazu o 90 stopni !!!\n\n");

}

/************************************************************************

                              PROGOWANIE
Funkcja, która wykonuje progowanie obrazu
PRE:
   Podany argument wiersza polecen jakiej wartosci progowania oczekujemy
i struktura z danymi o obrazie
POST:
    Wykonanie progowania na obrazie 
**************************************************************************/

void Progowanie(T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  int i,j;
  int prog; // zmienna pomocniczna

  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
  
  prog=((obraz->szarosci)*(zm_pom->w_progu))/100; //wczytujemy wartosc progu
  
  for (i=0;i<obraz->wymy;i++) {/*Zastosowałem operator warunkowy ponieważ było to chyba najwygodniejszym rozwiazaniem */
    for (j=zm_pom->wybrany_kolor;   j<obraz->format*obraz->wymx;  zm_pom->wybrany_kolor_pom==WYBRANO_KOLOR?j+=3:j++){
      if(piksele[i][j]<=prog)
	piksele[i][j]=0;
      else
	piksele[i][j]=obraz->szarosci;
    }
  }
  printf("!!! Wykonano progowanie na obrazie !!!\n\n");  
}

/*************************************************************

                              KONTUROWANIE
Funkcja która wykonuje konturowanie obrazu
POST:
     Struktura z danymi o obrazie
PRE:
    Obraz, który został skonturowany
***************************************************************/
void Konturowanie (T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  int i,j;

  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;

  for (i=0;i<obraz->wymy;i++) {/*Zastosowałem operator warunkowy ponieważ było to chyba najwygodniejszym rozwiazaniem */
    for (j=zm_pom->wybrany_kolor;   j<obraz->format*obraz->wymx;  zm_pom->wybrany_kolor_pom==WYBRANO_KOLOR?j+=3:j++){
      piksele[i][j]=abs(piksele[i][j+obraz->format]-piksele[i][j])+abs(piksele[i+obraz->format][j]-piksele[i][j]);
    }
  }
  printf("!!! Wykonano konturowanie obrazu !!!\n\n");
}
