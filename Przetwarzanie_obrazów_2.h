/*Struktura do przechowywania informacji o obrazie PGM i PPM*/
typedef struct t_obraz {
  FILE *plik_we, *plik_wy;        /* uchwyty do pliku wej. i wyj. */
  char *nazwa_pliku_we; //tablice do przechowywania nazw plikow wejściowych i wyjściowych
  char *nazwa_pliku_wy;
  int wymx;
  int wymy;
  int szarosci;
  void *piksele;
  int format;
}T_OBRAZ;

/*Struktura do przechowywania zmiennych pomocniczych do obrazów*/
typedef struct zmienne_pom_do_obrazow{
  int odczytano;    //zawarta w funkcji Wczytaj_plik
  char *kolor; //zmienna pomocnicza w rozroznieniu koloru, gdy uzytkownik go podaje wtrakcie podawania argumentow wiersza polecen
  int wybrany_kolor;
  int wybrany_kolor_pom; //zmienna służąca do pomocy w rozroznieniu z jakim kolorem mamy doczynienia, znajdujaca sie w przetwarzanie_opcji() w fladze -m  
  int w_progu;              /* wartosc progu dla opcji progowanie */
  int opcja_z_menu; //Ta zmienna pomocnicza służy do pomocy rozróżniania, czy użytkownik wybrał opcje z menu ( czyli bez wpisywania argumentów wiersza polecen)
  char *nazwa_pom; // tablica dla nazwy pomocnieczej, służąca do przechowania nazwy "plik tymczasowy", gdy użytkownik będzie chciał wyśiwtlicz program bez zapisu
  
  /*zmienne pod komunikaty o błędach*/
  int zapisano;         //zmienna pomocnicza która daje znać czy zapsiano prawidłowo obraz , umieszczona w funkcji zapisz()
  int bez_menu;        //zmienna pomocnicza do komunikatow o bledach ( zawarta w funkcji przetwarzaj_opcje() w definicji opcji "i"
  int wypisano;       //zmienna pomocnicza do komunikatow o bledach znajduje sie w funkcji Wczytaj_plik() i w przetwarzaj_opcje() flaga -o
  int blad;            //zmienna pomocnicza jesli wystapil blad, powoduje ze program nie wyswietla odpowiedniego komunikatu ( ten komunikat jest zwarty w funkcji main() pod koniec
  int przetworzono;   //zmienna pomocnicza do rozroznienia czy uzytkownik korzysta z menu czy z agrumentow wiersza polecen ( zwarta jest ona w funkcji przetwarzaj opcje w funkcji switch w fladze -o i -d
}ZMIENNE_POM_DO_OBRAZOW;

/*Prototypy funkcji*/
void wyzeruj_opcje(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
int przetwarzaj_opcje(int, char **,T_OBRAZ *,ZMIENNE_POM_DO_OBRAZOW *);
int menu(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
int Przedstawienie_wyboru(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
int  Wczytaj_plik (T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
int  czytaj(FILE *, T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
int Zapisz(FILE *, T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
void wyswietl(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
int wyswietl_bez_zapisu(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
void wyzeruj_plik(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
void Negatyw (T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW * );
void konwersja_do_szarosci(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
void Obrot_o_90_stopni (T_OBRAZ * );
void Progowanie(T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
void Konturowanie (T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);
void wybor_koloru (T_OBRAZ *, ZMIENNE_POM_DO_OBRAZOW *);








  
