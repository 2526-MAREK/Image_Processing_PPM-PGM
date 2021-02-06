#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Przetwarzanie_obrazów_2.h"

/**************************************************************************************************
*  
*                                       CZYTAJ 
*
*   Funkcja, która wczytuje obraz PGM z pliku do tablicy       	       	       	       	    
*    
*   PRE:
*        Plik musi spełniać wymogi formatu .ppm lub .pgm
*   POST:
*        Funkcja wypełnia strukture T_OBRAZ danymi obrazu: format obrazu, wymiary obrazu( wymx,
*        wymy), odcienie (szarosci), piksele. Jeśli plik spełnia wymogi, funkcja zwraca iloczyn 
         wymiarów obrazu.


**************************************************************************************************/
int czytaj(FILE * plik_we, T_OBRAZ * obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;
  obraz->format=0;

  /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    zm_pom->blad=1;
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien byæ P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */
  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    obraz->format=NIE_PGM;
  }
  /*Sprawdzenie czy plik nie jest formatu .PPM */
  if(obraz->format==NIE_PGM)
    {
      if ( (buf[0]!='P') || (buf[1]!='3') || koniec ) {   /* Czy jest magiczne "P3"? */
	fprintf(stderr,"Blad: To nie jest plik PPM/PGM!!!\n");
	zm_pom->blad=1;
	return(0);
      }
      obraz->format=PPM;  // Jesli plik jest formatu .PPM to przypisz zmiennej która okresla format odpowiednia wartosc
    }
  if(obraz->format!=PPM)
    obraz->format=PGM;  //Jesli plik nie jest formatu .PPm to przypisz zmiennej ktora okresla format odpowiednia wartosc
  
  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",&(obraz->wymx),&(obraz->wymy),&(obraz->szarosci))!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    zm_pom->blad=1;
    return(0);
  }
  obraz->piksele=malloc(obraz->format*obraz->wymx*obraz->wymy*sizeof(int)); //alokacja pamięci dla tablicy PGM i PPM ( Jeśli plik jest formatu .PPM to alokuje 3 razy większa tablice od tablicy dla formatów .PGM 


  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;

  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<(obraz->wymy);i++) {
    for (j=0;j<(obraz->format*obraz->wymx);j++) {
      if (fscanf(plik_we,"%d",&(piksele[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	zm_pom->blad=1;
	return(0);
      }
    }
  }
  return (obraz->format*obraz->wymx)*(obraz->wymy);   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */

/********************************************************************************************************

                        ZAPISZ
 Funkcja, która zapisuje w pliku o danej nazwie, dane przetworzonego obrazu.                              
 PRE: 
       Prawidłowe przetworzone dane zapisane w strukturze obrazu.                                                
 POST:                                               
      Funkcja wypełnia plik przetworzonymi danymi obrazu: format obrazu, wymiary obrazu( wymx,
       wymy), odcienie (szarosci), piksele.                                           
*********************************************************************************************************/
int Zapisz (FILE *plik_wy, T_OBRAZ * obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  int i,j;
  char nazwa_pliku_wy[DL_LINII]; //Tworze tablice tymczasowa do przechowania nazwy wy
	
  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
	
  if(zm_pom->opcja_z_menu==B_BRAK_ARGUMENTOW_WIERSZA_POLECEN){	
    printf("Podaj nazwe pliku wyjsciowego:\n");
    scanf("%s", nazwa_pliku_wy);
    obraz->nazwa_pliku_wy=nazwa_pliku_wy;
  }
  
  plik_wy=fopen(obraz->nazwa_pliku_wy,"w");
  if (plik_wy != NULL) {       /* co spowoduje zakomentowanie tego warunku */
    /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
    if (plik_wy==NULL) {
      fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
      zm_pom->blad=1;
      return(0);
    }
  
    /*Program przypisuje do pliku odpowiednie dane w zależności od formatu pliku ( .PPM czy . PGM ) */
    if(obraz->format==PGM){
      fprintf(plik_wy,"P2\n");
      fprintf(plik_wy,"%d %d\n%d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
    }
    else if(obraz->format==PPM){
      fprintf(plik_wy,"P3\n");
      fprintf(plik_wy,"%d %d\n%d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
    }

    for(i=0;i<obraz->wymy;i++){                  //Funkcja for która zwiększa liczbe wierszy
      for(j=0;j<obraz->format*obraz->wymx;j++){//Zagnieżdżona funkcja for która zwiększa liczbe kolumn i wypisuje cała tablic
	if((piksele[i][j]>=0)&&(piksele[i][j])<10)
	  fprintf(plik_wy,"%d   ", piksele[i][j]);
	if((piksele[i][j]>=10)&&(piksele[i][j]<100))
	  fprintf(plik_wy,"%d  ", piksele[i][j]);
	if((piksele[i][j]>=100)&&(piksele[i][j]<1000))
	  fprintf(plik_wy,"%d ", piksele[i][j]);
	if(j==obraz->wymx){                      //Jeśli kończą się wiersze to przejdz do nowej lini
	  fprintf(plik_wy,"\n");
	}    
      }
    }
    fclose(plik_wy);
    zm_pom->zapisano=GOTOWE;
    return(0);
  }
}
