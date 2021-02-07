//Marek Szulak

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Przetwarzanie_obrazów_2.h"

/********************************************************************/
/*                                                                  */
/* ALTERNATYWNA DO PRZEDSTAWIONEJ NA WYKLADZIE WERSJA OPRACOWANIA   */
/* PARAMETROW WYWOLANIA PROGRAMU UWZGLEDNIAJACA OPCJE Z PARAMETRAMI */
/* Z ODPOWIEDNIO ZAPROPONOWANYMI STRUKTURAMI DANYCH PRZEKAZUJACYMI  */
/* WCZYTANE USTAWIENIA                                              */
/*                                    COPYRIGHT (c) 2007-2013 ZPCiR */
/*                                                                  */
/* Autorzy udzielaja kazdemu prawa do kopiowania tego programu      */
/* w calosci lub czesci i wykorzystania go w dowolnym celu, pod     */
/* warunkiem zacytowania zrodla                                     */
/*                                                                  */
/********************************************************************/

/*********************************************************************************************************

                                       MAIN
Funkcja główna , która wywołuje odpowiednie funkcje w zależnosci od wyboru użytkownika
PRE:
    Argumenty wiersza polecen
POST:
    Opcja programu z argumentami wiersza polecen lub wyswietlajace się menu, komunikacja o błedach, 
 funkcja po calej pracy programu zeruje zalokowana pamieć przez tablice obrazu jeśli alokacja nastąpiła
***********************************************************************************************************/

int main(int argc, char ** argv){ 
  T_OBRAZ obraz;
  ZMIENNE_POM_DO_OBRAZOW zm_pom;

  wyzeruj_opcje(&obraz, &zm_pom);
  
  zm_pom.opcja_z_menu=przetwarzaj_opcje(argc,argv,&obraz, &zm_pom);

  /*komunikaty o błędach*/
  if(zm_pom.opcja_z_menu==B_BRAK_OPCJI_o){//Musialem dopisac ta opcje poniewaz tablica "nazwa_pliju_wy" musi posaidac nazwe w nastepenej funkcji warunkowej if , a jesli ten if sie urochomi uzytkownik musial nie wpisac nazwy a wiec wpisze w to miejsce "byle co" aby nastepny warunek zadzialal bez problemu
    obraz.nazwa_pliku_wy="nic"; 
  }
  if((zm_pom.opcja_z_menu==B_BRAK_OPCJI_o)&&(zm_pom.odczytano!=0)&&(strcmp(obraz.nazwa_pliku_wy,"-")!=0)&&(zm_pom.zapisano==0)&&(zm_pom.wypisano==0)){
    obraz.plik_wy=stdout; //Wypisujemy obraz na standardowym wyjsciu
    printf("Wypisano obraz na standardowym wyjściu\n");
  }
  if((zm_pom.opcja_z_menu==B_BRAKNAZWY)&&(zm_pom.wypisano==0)&&(zm_pom.odczytano!=0)){          //zmienna wypisano informuje o tym czy wypisano poprzednie komunikaty o blędach aby sie nie nakładały podczas wyświetlania 
    printf("Nie podano nazwy do zapisu!, poprawna składnia wywołania programu:\n");  
    printf("'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)]");
    printf("[-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'\n\n");
    printf("!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność ");
    printf("może to dać nieoczekiwane efekty !!!\n\n");
    printf("Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'\n");
    zm_pom.blad=1;
    zm_pom.wypisano=1;
  }
    
  if((zm_pom.opcja_z_menu==B_NIEPOPRAWNAOPCJA)&&(zm_pom.wypisano==0)){   //Jesli wpisano niepoprawna opcje 
    printf("Prawdopodobnie wpisujesz niepoprawna opcje, poprawna składnia wywołania programu:\n");
    printf("'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)]");
    printf("[-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'\n\n");
    printf("!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność ");
    printf("może to dać nieoczekiwane efekty !!!\n\n");
    printf("Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'\n");
    zm_pom.blad=1;
  }
  if(((zm_pom.opcja_z_menu==B_BRAKPLIKU)||(zm_pom.opcja_z_menu==B_BRAKNAZWY)) && ((argc-1)!=0)&&(zm_pom.wypisano==0)&&(zm_pom.blad!=1)){   //Jeśli w wierszu polecen pojawia sie argumenty ale nie podano uchwytu do pliku_we 
    printf("Niestety nie wczytujesz żadnego pliku, poprawna składnia wywołania programu:\n");
    printf("'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)]");
    printf("[-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'\n\n");
    printf("!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność ");
    printf("może to dać nieoczekiwane efekty !!!\n\n");
    printf("Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'\n");
    zm_pom.blad=1;
  }

  zm_pom.argc_pom = argc-1;
  /* Jesli użytkownik nie poda argumentow wiersza polecen wyswietla sie menu*/
  if((zm_pom.opcja_z_menu==B_BRAK_ARGUMENTOW_WIERSZA_POLECEN)&&((zm_pom.argc_pom)==0))
    menu(&obraz, &zm_pom);

  if((zm_pom.odczytano!=0)&&(obraz.plik_we!=0)){
    free(obraz.piksele);  // zwolnienie pamiec zajetej przez nasza tablice zawierajca dane o obrazie 
  }
  
  return 0;
  }

/***************************************************************************

                      WYZERUJ_OPCJE
 Funkcja inicjuje strukture wskazywana przez wybor i zm_pom   
 PRE:                                                
      Brak
 POST:                                               
      "wyzerowana" struktury T_OBRAZ i ZMIENNE_POM_DO_OBRAZOW   
****************************************************************************/
void wyzeruj_opcje(T_OBRAZ * wybor,ZMIENNE_POM_DO_OBRAZOW *zm_pom) {
  wybor->plik_we=NULL;
  wybor->plik_wy=NULL;
  zm_pom->odczytano=0;
  zm_pom->zapisano=0;
  zm_pom->bez_menu=0;
  zm_pom->wypisano=0;
  zm_pom->blad=0;
  zm_pom->przetworzono=0;
  zm_pom->wybrany_kolor=0;//Obraz kolorowy 
  zm_pom->wybrany_kolor_pom=0;
  zm_pom->nazwa_pom="nic"; //Wpisuje "nic" do tablicy nazwa_pom aby w funkcji wysiwietl nie pojawial sie blad pamieci
}

/************************************************************************/
/*                       
                              PRZETWARZAJ OPCJE   
                  
   
   Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv  */
/* i zapisuje je w strukturze wybor                                     */
/* Skladnia opcji wywolania programu                                    */
/* ./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] 
[-m (r, g, b ,s)] [-p liczba] [-n] [-k] [-t] 
 [-o nazwa(bez spacji)]  [-d] }  */
/* Argumenty funkcji:                                                   */
/*         argc  -  liczba argumentow wywolania wraz z nazwa programu   */
/*         argv  -  tablica argumentow wywolania                        */
/*         obraz -  struktura z informacjami o obrazie
           zm_pom - Struktura ze zmiennymi pomocniczymi       */
/* PRE:                                                                 */
/*      brak                                                            */
/* POST:                                                                */
/*      funkcja otwiera odpowiednie pliki, zwraca uchwyty do nich       */
/*      w strukturze wybór, do tego ustawia na 1 pola, ktore            */
/*	poprawnie wystapily w linii wywolania programu,                 */
/*	pola opcji nie wystepujacych w wywolaniu ustawione sa na 0;     */
/*	zwraca wartosc W_OK, gdy wywolanie bylo poprawne                */
/*	lub kod bledu zdefiniowany stalymi B_* (<0)                     */
/* UWAGA:                                                               */
/*      funkcja nie sprawdza istnienia i praw dostepu do plikow         */
/*      w takich przypadkach zwracane uchwyty maja wartosc NULL         */
/************************************************************************/
int przetwarzaj_opcje(int argc, char **argv, T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom) {
  int i, prog;
  
  obraz->plik_wy=stdout;        /* na wypadek gdy nie podano opcji "-o" */

  for (i=1; i<argc; i++) {
    if (argv[i][0] != '-')  /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA; 
    switch (argv[i][1]) {
    case 'i': {                 /* opcja z nazwa pliku wejsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */
	obraz->nazwa_pliku_we=argv[i];	
	if (strcmp(obraz->nazwa_pliku_we,"-")==0){ /* gdy nazwa jest "-"        */
	  obraz->plik_we=stdin;            /* ustwiamy wejscie na stdin */
	  printf("Obraz wczytywany ze standardowego wejścia\n");
	  break;
	}
       else{                               /* otwieramy wskazany plik   */
	  zm_pom->bez_menu=1;            //zmienna pomocnicza do komunikatow o bledach
	  Wczytaj_plik(obraz, zm_pom);
	  break;
       }
      } else 
	return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
      break;
    }
    case 'm':{  /*mamy wykonać wybór koloru do przetwarzania lub konwersja do szarosci */
      if(obraz->format!=PPM){
	printf("Niestety flaga -m jest tylko dla obrazów kolorowych\n");
	return B_BRAKWARTOSCI; /*bład nie wczytano pliku PPM*/
      }
      else{
	if (++i<argc){	  /* wczytujemy kolejny argument jako symbole kolorów */
	  zm_pom->kolor=argv[i];
	  if((strcmp(zm_pom->kolor, "r")==0)||(strcmp(zm_pom->kolor, "g")==0)||(strcmp(zm_pom->kolor, "b")==0)||(strcmp(zm_pom->kolor, "s")==0)){ // jesli argument wiersza polecen zaraz po fladze -m jest r lub , g, lub ,b, lub s to wykonaj
	    zm_pom->wybrany_kolor_pom=WYBRANO_KOLOR;
	    if(strcmp(zm_pom->kolor, "r")==0)
	      zm_pom->wybrany_kolor=RED;
	    if(strcmp(zm_pom->kolor, "g")==0)
	      zm_pom->wybrany_kolor=GREEN;
	    if(strcmp(zm_pom->kolor, "b")==0)
	      zm_pom->wybrany_kolor=BLUE;
	    if(strcmp(zm_pom->kolor, "s")==0){
	      konwersja_do_szarosci(obraz, zm_pom);
	    }
	    break;
	  }/*Jeśli użytkownik poda zla opcje zaraz po fladze -m*/
	  else{
	    printf("Jeśli korzystasz z flagi -m to zaraz po niej musisz wybrać odpowiedni kolor do przetwarzania: \n");
	    printf("dla przykładu -m r, gdzie:\nr-czerwony\ng-zielony\nb-niebieski\ns-konwersja obrazu kolorowego do szarego\n");
	    return B_BRAKWARTOSCI; //błąd zła wartosc po fladze -m
	  }/* jeśli użytkownik po fladze -m nic nie wpisze */
	}else{
	  printf("Jeśli korzystasz z flagi -m to zaraz po niej musisz wybrać odpowiedni kolor do przetwarzania: \n");
	  printf("dla przykładu -m r, gdzie:\nr-czerwony\ng-zielony\nb-niebieski\ns-konwersja obrazu kolorowego do szarego\n");
	  return B_BRAKWARTOSCI; //błąd brak wartosci po fladze -m
	}
      }
      break;
    }
    case 'p': {  /*Mamy wykonąc progowanie*/
      if (++i<argc) { /* wczytujemy kolejny argument jako wartosc progu */
	if ((sscanf(argv[i],"%d",&zm_pom->w_progu)==1)&&((zm_pom->w_progu)>=0)&&((zm_pom->w_progu)<=100)) {
	  Progowanie(obraz, zm_pom);
	} else{
	  printf("Niestety podałeś niepoprawna wartość progu lub wogole jej nie podales pamietaj\n ");
	  printf("przedział wartosci progowania to od 0 do 100\n");
	  printf("Przykład użycia flagi: -p <wartosc z przedzialu>\n");
	  return B_BRAKWARTOSCI;     /* blad: niepoprawna wartosc progu */
	}
      } else {
	printf("Niestety podałeś niepoprawna wartość progu lub wogole jej nie podales pamietaj\n");
	printf("przedział wartosci progowania to od 0 do 100\n");
	printf("Przykład użycia flagi: -p <wartosc z przedzialu>\n");
	return B_BRAKWARTOSCI;             /* blad: brak wartosci progu */
      }
      break;
    }
    case 'n': {                 /* mamy wykonac negatyw */
      if(zm_pom->odczytano!=0)
	Negatyw(obraz, zm_pom);
      break;
    }
    case 'k': {                 /* mamy wykonac konturowanie */
      if(zm_pom->odczytano!=0)
	Konturowanie(obraz, zm_pom);
      break;
    }
    case 't':{                /* mamy wykonac obrot o 90 stopni */
      if((zm_pom->odczytano!=0)&&(obraz->format==PGM))
	Obrot_o_90_stopni(obraz);
      else
	printf("Obrot obrazu o 90 stopni działa tylko dla obrazow pgm, skonwertuj swój obraz za pomoca flagi -m s\n");
      break;
    }
    case 'o': {                 /* opcja z nazwa pliku wyjsciowego */
      if (++i<argc) {   /* wczytujemy kolejny argument jako nazwe pliku */	
	obraz->nazwa_pliku_wy=argv[i];
	
	if (strcmp(obraz->nazwa_pliku_wy,"-")==0){/* gdy nazwa jest "-"         */
	  obraz->plik_wy=stdout;          /* ustwiamy wyjscie na stdout */
	  printf("Wypisano obraz na standardowym wyjściu\n");
	  zm_pom->wypisano=1;
	  return W_OK;
	}
	else
	  {                              /* otwieramy wskazany plik    */
	    if((obraz->plik_we!=NULL)&&(zm_pom->odczytano!=0)){
	      Zapisz(obraz->plik_wy, obraz, zm_pom);
	    }
	  }	
      }
	else 
	  return B_BRAKNAZWY;                   /* blad: brak nazwy pliku */
	break;
      }
    case 'd': {                 /* mamy wyswietlic obraz */
      if(zm_pom->odczytano!=0){
	zm_pom->przetworzono=1;
	wyswietl(obraz, zm_pom);
	break;
      }else
      break;
    }
    default:                    /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /*koniec switch */
  } /* koniec for */

  if (obraz->plik_we!=NULL)     /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else 
    return B_BRAKPLIKU;         /* blad:  nie otwarto pliku wejsciowego  */
}
/**********************************************************************************

                          MENU 
  Funkcja, która realizuje funkcja switch jako menu programu                            
PRE:                                                
    Prawidłowe dane wprowadzone przez użytkownika                                           
POST:                                               
     Wykonanie odpowiednich funkcji wybranych przez użytkownika programu                                          
**********************************************************************************/
int menu(T_OBRAZ * obraz, ZMIENNE_POM_DO_OBRAZOW * zm_pom){
  int wybor;                                               //Deklaracja zmiennej wybor

  while((wybor=Przedstawienie_wyboru(obraz, zm_pom)) != 10 )                         //petla while która pozwala operować menu dopoki uzytkownik nie wpisze 10
    {
      switch(wybor)                                          //Wywo³anie funkcji switch która pozwala na wybór  w menu
	{
	case(1):
	  {
	    zm_pom->odczytano=Wczytaj_plik(obraz, zm_pom);

	    break;                                          // Funkcja break pozwalaj±ca na przerwanie wykonywania funkcji switch po danym wyborze i pozwalajaca przejsc dalej
	  }
	case(2):
	  {
	    if(zm_pom->odczytano!=0)
	    Negatyw (obraz, zm_pom);
	    else
	      printf("Nie wczytano pliku\n");
	    break;
	  }
	case(3):
	  {
	    if(zm_pom->odczytano!=0){
	    printf("Podaj jaki procent progowania chcesz dokonac: ");

	    /*Zabezpieczenie przed wpisaniem przez użytkownika złych danych(np liter)*/
	    while(scanf("%d", &zm_pom->w_progu)!=1){ //dopoki nie udało się wczytać 
	      int pom; //zmienna pomocniczna
	      while((pom = getchar()) != '\n' && pom != EOF); // pętla wyciągająca znaki z bufora
	      break;
	    }
	    
	    if(((zm_pom->w_progu)>=0)&&((zm_pom->w_progu)<=100))
	    Progowanie (obraz, zm_pom);
	    else
	      printf("Podano niewlasciwa wartość progu, przedzial tej wartosci to od 0 do 100\n");
	    }
	    else
	    printf("Nie wczytano pliku\n");
	    break;
	  }
	case(4):
	  {
	    if(zm_pom->odczytano!=0)
	    Konturowanie (obraz, zm_pom);
	    else
	    printf("Nie wczytano pliku\n");
	    break;
	  }
	case(5):
	  {
	    if((zm_pom->odczytano!=0)&&(obraz->format==PGM))
	    Obrot_o_90_stopni(obraz);
	    else
	      printf("Obrot obrazu o 90 stopni działa tylko dla obrazow pgm, skonwertuj swój obraz za pomoca opcji 6 s\n");
	    break;
	  }
	case(6):
	  {
	    if((zm_pom->odczytano!=0)&&(obraz->format==PPM))
	    konwersja_do_szarosci(obraz, zm_pom);
	    else
	    printf("Ta opcja jest tylko dla obrazów kolorowych (format PPM)\n");
	    break;
	  }
	  
	case(7):
	  {
	    if(zm_pom->odczytano!=0)
	    wybor_koloru(obraz, zm_pom);
	    else
	    printf("Nie wczytano pliku\n");
	    break;
	  }
	case(8):
	  {
	    if(zm_pom->odczytano!=0)
	    Zapisz (obraz->plik_wy, obraz, zm_pom);
	    else

	    printf("Nie wczytano pliku\n");
	    break;
	  }
	case(9):
	  {
	    if(zm_pom->odczytano!=0)
	    wyswietl (obraz, zm_pom);
	    else
	    printf("Nie wczytano pliku\n");
	  break;
	  }
	default:{
	  printf("Mozesz wpisac tylko liczby w przedziale od 1 do 10! ;) \n" );
	}
	}
    }
  return 0;
}
/***********************************************************************************************************

                                              PRZEDSTAWIENIE_WYBORU
Funkcja przedstawia menu jakie użytkownik może wykorzystać w programie, jeśli wybierze taką opcję.
PRE:
    Prawidłowo wprowadzone dane przez użytkownika(np. czy użytkownik wprowadził liczbę całkowita itp.).
POST:
     Funkcja zwraca wartość jaka wybrał użytkownik.
************************************************************************************************************/
 int Przedstawienie_wyboru(T_OBRAZ * obraz, ZMIENNE_POM_DO_OBRAZOW * zm_pom){
  int wybor;

  printf("Menu:\n");
  if((zm_pom->odczytano!=0)&&(obraz->format==PGM)){
     printf("1 - Wczytaj plik PGM/PPM !!! Wczytano plik PGM o nazwie: %s !!!\n", obraz->nazwa_pliku_we);
    }
  else if((zm_pom->odczytano!=0)&&(obraz->format==PPM)){
     printf("1 - Wczytaj plik PGM/PPM !!! Wczytano plik PPM o nazwie: %s !!!\n", obraz->nazwa_pliku_we);
    }
   else{
  printf("1 - Wczytaj plik PGM/PPM\n");
   }
  printf("2 - Negatyw\n");
  printf("3 - Progowanie \n");
  printf("4 - Konturowanie \n");
  printf("5 - Obrot obrazka o 90 stopni\n");
  printf("6 - Konwersja do formatu PGM(szarosci)\n");
  printf("7 - Wybór koloru do przetwarzania\n");
  printf("8 - Zapisz pod nazwa przetworzony plik\n");
  printf("9 - Wyswietl obraz\n");
  printf("10 - Zakoncz dzialanie\n");
  printf("Twoj wybor: ");
	
  /*Zabezpieczenie przed wpisaniem przez użytkownika złych danych(np liter)*/
  while(scanf("%d",&wybor)!=1){ //dopoki nie udało się wczytać 

    int pom; //zmienna pomocniczna
    while((pom = getchar()) != '\n' && pom != EOF); // pętla wyciągająca znaki z bufora
    break;
  }
	
  return wybor;
}

/*************************************************************************************
 
                          WYBOR_KOLORU
Funkcja pozwalajaca wybrać kolor do przetwarzania, gdy użytkownik korzysta z menu
PRE:
    Obraz kolorowy i prawidłowe dane wprowadzone przez użytkownik
POST:
    zapisanie w zmiennej wybrany_kolor informacji o tym jaki kolor użytkownik wybrał
*************************************************************************************/
void wybor_koloru(T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  int wybor;
  
  if(obraz->format!=PPM){
    printf("Kolor do przetwarzania można wybrać tylko dla obrazów o formacie PPM(kolorowym)\n");
  }
  else{
    printf("Wybierz kolor do przetwarzania:\n");
    printf("1 - czerwony\n2 - zielony\n3 - niebieski\n");
    printf("Wybierz: ");
    
    /*Zabezpieczenie przed wpisaniem przez użytkownika złych danych(np liter)*/
    while(scanf("%d",&wybor)!=1){ //dopoki nie udało się wczytać 
      int pom; //zmienna pomocniczna
      while((pom = getchar()) != '\n' && pom != EOF); // pętla wyciągająca znaki z bufora
      break;
    }

    switch(wybor)
      {
      case(1):
	{
	  zm_pom->wybrany_kolor=RED;
	  printf("Wybrano czerowny kolor do przetwarzania!\n");
	  break;
	}
      case(2):
	{
	  zm_pom->wybrany_kolor=GREEN;
	  printf("Wybrano zielony kolor do przetwarzania!\n");
	break;
	}
      case(3):
	{
	  zm_pom->wybrany_kolor=BLUE;
	  printf("Wybrano niebieski kolor do przetwarzania!\n");
	break;
	}
      default:
	  {
	    printf("Możesz wpisać tylko liczby od 1 do 3");
	    break;
	  }
      }
  }
}

/*************************************************************************************

                        WCZYTAJ_PLIK
Funkcja, która wczytuje nazwę pliku wejściowego i tworzy do niego uchwyt
PRE:
   Brak
POST:
     Stworzony uchwyt do pliku wejsciowego i odczytana jego nazwa funkcja zwraca  
wartość zwróconą przez funkcje czytaj
***************************************************************************************/
 int Wczytaj_plik (T_OBRAZ * obraz, ZMIENNE_POM_DO_OBRAZOW * zm_pom){
  char nazwa_pliku_we[DL_LINII]; //Tworze tablice tymczasowa do przechowania nazwy we
  
  /*Opcja jeśli użytkownik zdecyduje się wczytać kolejny plik, podczas korzystania z menu*/
  if((zm_pom->odczytano!=0)&&(obraz->plik_we!=NULL))
    wyzeruj_plik(obraz, zm_pom);
  
   /* Wczytanie zawartosci wskazanego pliku do pamieci */
  if(zm_pom->opcja_z_menu==B_BRAK_ARGUMENTOW_WIERSZA_POLECEN){
  printf("Podaj nazwe pliku wejsciowego:\n");
  scanf("%s", nazwa_pliku_we);
  obraz->nazwa_pliku_we=nazwa_pliku_we;
  }
  
  obraz->plik_we=fopen(obraz->nazwa_pliku_we,"r");
  if (obraz->plik_we!= NULL) {       /* co spowoduje zakomentowanie tego warunku */
       zm_pom->odczytano = czytaj(obraz->plik_we, obraz, zm_pom);
     fclose(obraz->plik_we);
     }
     else{
       if(zm_pom->bez_menu==1){
	 printf("Niestety nie wcpzytujesz żadnego pliku, poprawna składnia wywołania programu:\n");
	 printf("'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)]");
	 printf("[-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'\n\n");
	 printf("!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność ");
	 printf("może to dać nieoczekiwane efekty !!!\n\n");
	 printf("Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'\n\n");
	 zm_pom->wypisano=1;   //zmienna pomocnicza do komunikatow o bledach 
       }
       printf("Sprawdź proszę czy napewno wczytujesz odpowiedni plik i czy ten plik który chcesz wczytać napewno znajduje się w tym samym katalogu co plik wykonywalny(./Przetwarzanie_Obrazów.out)!\n");
       zm_pom->blad=1;
     }
 
  return zm_pom->odczytano ;
}

/**********************************************************************************

                              WYSWIETL
Funkcja wyświetl, która wyświetla obraz na ekranie za pomoca programu display
PRE:
    wczytany obraz do pamieci
POST:
     Wyswietlenie danego obrazu za pomoca progrmau display na ekranie komputera
*************************************************************************************/
void wyswietl(T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom) {

  char polecenie[DL_LINII];      /* bufor pomocniczy do zestawienia polecenia */
  char *nazwa=NULL;
  char *nazwa_tym=obraz->nazwa_pliku_we;

  /*Opcja jeśli użytkownik nie zapisze jeszcze przetworzonego obrazu i chce go wyświetlić*/
  if((zm_pom->zapisano!=GOTOWE)&&(obraz->plik_we!=NULL)){
 wyswietl_bez_zapisu(obraz, zm_pom);
 nazwa=zm_pom->nazwa_pom;
  }
    else{// if((obraz->plik_we!=NULL)&&(zm_pom->zapisano==GOTOWE)&&(obraz->plik_wy!=NULL)){
      if((zm_pom->opcja_z_menu==B_BRAK_ARGUMENTOW_WIERSZA_POLECEN)&&((zm_pom->argc_pom)==0))//Jeśli użytkownik korzysta z menu
	nazwa = obraz->nazwa_pliku_wy_tym;
      else
	nazwa=obraz->nazwa_pliku_wy; // Tu jest problem, gdy uzytkownik wybierze menu 
    }

  if (zm_pom->odczytano != 0){
  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie, nazwa);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
  }
  else{
    printf("Aby wyświetlić obraz należy najpierw go wczytać\n");
    zm_pom->blad=1;
  }
  /*Zastosowałem taka opcje jak poniżej ponieważ nie miałem pomyslu jak zatrzymać program( gdy wpisujemy argumenty wiersza polecen) plik tymczasowy usuwal się zbyt szybko i nawet się nie wyświetlal*/
  if(zm_pom->przetworzono==1){
    printf("Wciśnij enter aby zakończyć\n");
    getchar();
  }

  if(zm_pom->opcja_z_menu==B_BRAK_ARGUMENTOW_WIERSZA_POLECEN){
    printf("Wciśnij enter aby przejść do menu\n");
    getchar();
    getchar();
  }
 
  if(((strcmp(zm_pom->nazwa_pom, nazwa)==0)&&(zm_pom->przetworzono==1))||(zm_pom->opcja_z_menu==B_BRAK_ARGUMENTOW_WIERSZA_POLECEN)){ //jesli mamy doczynienia z "plikiem tymczasowym" i korzystamy z argumentow wiersza polecen
    remove(zm_pom->nazwa_pom);  // usuniecie pliku tymczasowego
    }
}
/****************************************************************************************************
   
                                     WYSWIETL_BEZ_ZAPISU
Funkcja, ktora pozwala na wyświetlanie obrazu bez zapisu go pod dana nazwa
PRE:
    Brak
POST:
     Utworzony plik tymczasowy z obrazem, który pozwala wyświetlac obraz bez zapisania go pod nazwa
*******************************************************************************************************/
int wyswietl_bez_zapisu(T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  FILE *plik_pom; //uchwyt do pliku pomocniczego do wyswietlania niezapisanego obrazu
  int i,j;
  int (*piksele)[obraz->format*obraz->wymx];
  piksele=(int(*)[obraz->format*obraz->wymx]) obraz->piksele;
  
  zm_pom->nazwa_pom="plik_tymczasowy";
  
  plik_pom=fopen(zm_pom->nazwa_pom,"w");

      if (plik_pom != NULL) {       /* co spowoduje zakomentowanie tego warunku */
        /*Sprawdzenie czy podano prawid³owy uchwyt pliku */
  if (plik_pom==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    zm_pom->blad=1;
    return(0);
  }
  
  /*Program przypisuje do pliku odpowiednie dane w zależności od formatu pliku ( .PPM czy . PGM ) */
  if(obraz->format==PGM){
  fprintf(plik_pom,"P2\n");
  fprintf(plik_pom,"%d %d %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
  }
  else if(obraz->format==PPM){
  fprintf(plik_pom,"P3\n");
  fprintf(plik_pom,"%d %d %d\n", obraz->wymx, obraz->wymy, obraz->szarosci);
  }
  
    for (i=0;i<obraz->wymy;i++) {
      for (j=0;j<obraz->format*obraz->wymx;j++) {
	fprintf(plik_pom,"%d\n",piksele[i][j]);
      }
    }
    fclose(plik_pom);

      }
}
/***********************************************************************************************

                                          WYZERUJ_PLIK
Funkcja, która zeruje cały plik.
PRE:
    Stary wypełniony plik z danymi.
POST:
     Pamieć i uchwyty do plików przygotowane do nastepnego wczytania kolejnego pliku.
***********************************************************************************************/
void wyzeruj_plik(T_OBRAZ *obraz, ZMIENNE_POM_DO_OBRAZOW *zm_pom){
  obraz->plik_we=NULL;
  free(obraz->piksele);
  obraz->wymx=0;
  obraz->wymy=0;
  obraz->szarosci=0;
  obraz->format=0;
  obraz->plik_wy=NULL;
}

