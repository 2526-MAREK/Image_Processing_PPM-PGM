# Project Name
Image_Processing_PPM/PGM

## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [How to use](#how-to-use)
* [Options](#options)
* [Status](#status)
* [Inspiration](#inspiration)
* [Test](#test)
* [Contact](#contact)

## General info
Program processes Images about format PPM and PGM with choosen option [Features](#features)

## Technologies
Language C ANSI C99

## How to use

In terminal[(BASH/SHELL)launched in folder where find your Image_processing_PPM-PGM] first you must compile program, writing: make

In folder where find Image_processing_PPM-PGM you must have some image with format PPM/PGM (In my pack you find two image with this format: kubus.pgm and Lena.ppm)

Next you must launch program, writing: ./Przetwarzanie_Obrazów.out ( Version with menu)(only Polish version)

Or you must launch program with options: ./Przetwarzanie_Obrazów.out [Options](#options)

!!! You must remember, that options must entered with set order !!! 

The ability to call the program(the pattern of the appropriate typing order):
./Przetwarzanie_Obrazów.out {[-i name(without space,tabluator)] [-m (r, g, b ,s)] [-p number] [-n] [-k] [-t] [-o name(without space,tabulator)]  [-d] }

## Features

-i <name_file> name file to loaded
-o <name_file> name file to write
-d Image should was displayed
-m <colour> choosing colors to processing: r - red, g - green, b - blue, s - conversion to grey(only for image with format PPM)
-n negative
-p <threshold> thresholding with a threshold with a given percentage value. Threshold belongs to compartment from 0 to 100
-t rotation image PGM about 90 degrees
-k contouring 

## Status
Only Polish version(I will upgrade this, in the closest future)
Program want to repair:
(This is descriptioned in TEST 15, TEST 16, TEST 17)(Only polish version)  [Test](#test) 

## Inspiration
I have inspirated frome this link(only polish version): https://kcir.pwr.edu.pl/~mucha/PProg/PProg_lab_05/opcje.c
All the rest programe is created by me.

## Test
Program tests only in polish version(I will upgrade this, in the closest future)

/*TESTY PROGRAMU*/
/*Pare testów są wspólne dla obrazów o formacie ppm i pgm i od nich zaczne*/
/*Są to testy sprawdzające zgodność programu z polceniem zadania do wykonania */
/* 1 TEST
Test działania: "(jeśli zamiast nazwy podany będzie znak '-' to zamiast z pliku obraz powinien być wczytywany ze standardowego wejścia)" ~ cytat z polecenia do zadania

Dane wejściowe:
 ./Przetwarzanie_Obrazów.out -i - -k -o test.pgm

Dane wyjściowe:
Wyświetla się napis informujący, że:
"Obraz wczytywany ze standardowego wejścia"

Program działa prawidłowo, zgodnie z poleceniem
 */

/* 2 TEST

Test działania: "(jeśli zamiast nazwy podany będzie znak '-' to zamiast do pliku obraz powinien być wypisany na standardowym wyjściu)" ~ cytat z polecenia do zadania

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i kubus.pgm -k -o -

Dane wyjściowe:
Wyświetla się napis informujący, że:
"Wypisano obraz na standardowym wyjściu"

Program działa prawidłowo, zgodnie z poleceniem
 */

/* 3 TEST
Test działania: "-d obraz po przetworzeniu powinien zostać wyświetlony"~ cytat z polecenia do zadania
Dane wejściowe:
./Przetwarzanie_Obrazów.out -i kubus.pgm -d

Dane wyjściowe:
komunikat informujacy:
"display plik_tymczasowy &
Wciśnij enter aby zakończyć

Wypisano obraz na standardowym wyjściu"

Wczytany obraz wyświetla się i po wciśnieciu enter obraz wypisuje się na standardowym wyjściu
Program działa prawidłowo, zgodnie z poleceniem
 */

/* 4 TEST
Test działania: "brak nazw plików po opcjach -i, -o oraz wartości progu po -p powinny spowodować odpowiedni komunikat o błędzie" ~ cytat z polecenia do zadania 

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i kubus.pgm -o

Dane wyjściowe:
Komunikat informujacy:
"Nie podano nazwy do zapisu!, poprawna składnia wywołania programu:
'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)][-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'

!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność może to dać nieoczekiwane efekty !!!

Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'"

Program działa prawidłowo zgodnie z poleceniem.
 */

/* 5 TEST
Test działania: "brak nazw plików po opcjach -i, -o oraz wartości progu po -p powinny spowodować odpowiedni komunikat o błędzie" ~ cytat z polecenia do zadania 

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i -o test

Dane wyjściowe:
komunikat o błędzie
"Niestety nie wczytujesz żadnego pliku, poprawna składnia wywołania programu:
'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)][-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'

!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność może to dać nieoczekiwane efekty !!!

Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'

Sprawdź proszę czy napewno wczytujesz odpowiedni plik i czy ten plik który chcesz wczytać napewno znajduje się w tym samym katalogu co plik wykonywalny(Przetwarzanie_Obrazów.out)!"

Program działa zgodnie z poleceniem
 */

/* 6 TEST
Test działania: "brak nazw plików po opcjach -i, -o oraz wartości progu po -p powinny spowodować odpowiedni komunikat o błędzie" ~ cytat z polecenia do zadania 

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i kubus.pgm -p  -o test

Dane wyjściowe:
komunikat o błędzie:
"Niestety podałeś niepoprawna wartość progu lub wogole jej nie podales pamietaj
 przedział wartosci progowania to od 0 do 100
Przykład użycia flagi: -p <wartosc z przedzialu>"

Program działa prawidłowo zgodnie z poleceniem
 */

/* 7 TEST
Test działania: "Opcja -i musi się pojawić przy wywołaniu programu"~cytat z polecenia do zadania

Dane wejściowe:
./Przetwarzanie_Obrazów.out  kubus.pgm -o test

Dane wyjściowe:
komunikat o błędzie:
"Prawdopodobnie wpisujesz niepoprawna opcje, poprawna składnia wywołania programu:
'./Przetwarzanie_Obrazów.out {[-i nazwa(bez spacji)] [-m (r, g, b ,s)][-p liczba] [-n] [-k] [-t] [-o nazwa(bez spacji)]  [-d] }'

!!! Pamietaj , że kolejność flag ma znaczenie, jeśli zmienisz kolejność może to dać nieoczekiwane efekty !!!

Lub skorzystaj z przejrzystego menu wpisując poprostu './Przetwarzanie_Obrazów.out'"
 */

/* 8 TEST
Sprawdzam czy flaga -m działa z obrazami pgm

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i kubus.pgm -m s -o test

Dane wyjściowe:
komunikat o błędzie:
"Niestety flaga -m jest tylko dla obrazów kolorowych"

Program działa prawidłowo


/*Przechodzę teraz do testów funkcji przetwarzania*/
/* 9 TEST
Sprawdzam poprawność flagi -m s a mianowcie konwersji ppm na pgm 

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i obraz.ppm -m s -o test
Plik wyglądający następująco:
P3
# feep.ppm
4 4
15
0 0 0  0 0 0   0 0 0   15 0 15
0 0 0  0 15 7  0 0 0    0 0 0
0 0 0  0 0 0   0 15 7   0 0 0
15 0   15 0 0  0 0 0 0   0 0 0

Dane wyjściowe:
P2
4 4
15
0   0   0   10  
0   7   0   0   
0   0   7   0   
10  0   0   0   

"!!! Wykonano konwersje obrazu kolorowego na szary !!!"


Program działa prawidłowo 

 */

/* 10 TEST
Sprawdzam działanie flagi -m r a mianowicie wybor koloru do przetwarzania w w tym przyapdku tylko kolor czerwony
Dane wejściowe:
./Przetwarzanie_Obrazów.out -i obraz.ppm -m r -n -o test
Plik wyglądający następująco:
P3
# feep.ppm
4 4
15
0 0 0     0 0 0   0 0 0   15 0 15
0 0 0    0 15 7  0 0 0    0 0 0
0 0 0    0 0 0   0 15 7   0 0 0
15 0 15  0 0 0   0 0 0   0 0 0

Dane wyjściowe:
P3
4 4
15
15  0   0   15  0   0   15  0   0   0   0   15  
15  0   0   15  15  7   15  0   0   15  0   0   
15  0   0   15  0   0   15  15  7   15  0   0   
0   0   15  15  0   0   15  0   0   15  0   0   

Program działa prawidłowo

"!!! Wykonano negatyw na obrazie !!! "

 */

/* 11 TEST 
Sprawdzam działanie flagi -m g a mianowicie wybor koloru do przetwarzania w w tym przyapdku tylko kolor czerwony

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i obraz.ppm -m g -n -o test
Plik wyglądający następująco:
P3
# feep.ppm
4 4
15
0 0 0     0 0 0   0 0 0   15 0 15
0 0 0    0 15 7  0 0 0    0 0 0
0 0 0    0 0 0   0 15 7   0 0 0
15 0 15  0 0 0   0 0 0   0 0 0

Dane wyjściowe:
P3
4 4
15
0   15  0   0   15  0   0   15  0   15  15  15  
0   15  0   0   0   7   0   15  0   0   15  0   
0   15  0   0   15  0   0   0   7   0   15  0   
15  15  15  0   15  0   0   15  0   0   15  0   

Program działa prawidłowo
Ogólnie flaga -m działa prawidłowo, więc rezygnuje z kolejnych testów tej flagi 
*/

/* 12 TEST 
Sprawdzam poprawność działania funkcji konturowanie

Dane wejściowe: 
./Przetwarzanie_Obrazów.out -i maly_2.pgm -k -o test
Plik wyglądający następujoco:
P2
# by hand
20 10
8
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0

Dane wyjściowe:
P2
20 10
8
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
7   7   7   7   7   7   7   7   7   14  7   7   7   7   7   7   7   7   7   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
0   0   0   0   0   0   0   0   0   7   0   0   0   0   0   0   0   0   0   7   
7   7   7   7   7   7   7   7   14  0   0   0   0   0   0   0   0   0   0   

!!! Wykonano konturowanie obrazu !!!

Program działa prawidłowo
*/

/* 13 TEST
Sprawdzenie dzialania funkcji progowania 

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i maly_2.pgm -p 50 -o test -d
Plik wygląda następująco:
P2
# by hand
20 10
8
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0

Dane wyjściowe:

P2
20 10
8
0   0   0   0   0   0   0   0   0   0   8   8   8   8   8   8   8   8   8   8   
0   0   0   0   0   0   0   0   0   0   8   8   8   8   8   8   8   8   8   8   
0   0   0   0   0   0   0   0   0   0   8   8   8   8   8   8   8   8   8   8   
0   0   0   0   0   0   0   0   0   0   8   8   8   8   8   8   8   8   8   8   
0   0   0   0   0   0   0   0   0   0   8   8   8   8   8   8   8   8   8   8   
8   8   8   8   8   8   8   8   8   8   0   0   0   0   0   0   0   0   0   0   
8   8   8   8   8   8   8   8   8   8   0   0   0   0   0   0   0   0   0   0   
8   8   8   8   8   8   8   8   8   8   0   0   0   0   0   0   0   0   0   0   
8   8   8   8   8   8   8   8   8   8   0   0   0   0   0   0   0   0   0   0   
8   8   8   8   8   8   8   8   8   8   0   0   0   0   0   0   0   0   0   0   

!!! Wykonano progowanie na obrazie !!!

Program działa prawidłowo

 */

/* 14 TEST 
Test funkcji obrot o 90 stopni

Dane wejściowe: 

Plik wygląda następująco:
P2
# by hand
20 10
8
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
0 0 0 0 0 0 0 0 0 0 7 7 7 7 7 7 7 7 7 7
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0
7 7 7 7 7 7 7 7 7 7 0 0 0 0 0 0 0 0 0 0

Dane wyjściowe: 
komunikat informujacy:
"!!! Wykonano obrot obrazu o 90 stopni !!!"

P2
10 20
8
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
7   7   7   7   7   0   0   0   0   0
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7
0   0   0   0   0   7   7   7   7   7   

Program działa prawidłowo

 */

/* TEST 15 
Sprawdzenie działania obrotu o 90 stopni dla obrazow ppm

Dane wejściowe:
./Przetwarzanie_Obrazów.out -i obraz.ppm -t -o test
Plik wygląda następująco:
P3
# feep.ppm
4 4
15
0 0 0  0 0 0   0 0 0   15 0 15
0 0 0  0 15 7  0 0 0    0 0 0
0 0 0  0 0 0   0 15 7   0 0 0
15 0   15 0 0  0 0 0 0   0 0 0

Dane wyjściowe:
"Obrot obrazu o 90 stopni działa tylko dla obrazow pgm, skonwertuj swój obraz za pomoca flagi -m s"

Niestety nie udało mi się zrealizowac funkcji obrotu dla obrazow ppm( Starałem się jak mogłem, lecz nie udało się) w funkcji obrotu zostawiłem troche przykładowego kodu kiedy się starałem, cały program został odpowiednio zabezpieczony, gdyby uzytkownik chciał obrocic obraz ppm 
*/

/* TEST 16
Nie wiem dlaczego nie działa wyświetlanie , gdy wpisze nastepujace wyrazenie:" ./Przetwarzanie_Obrazów.out -i maly_2.pgm -k -o test -d"  Wygląda to tak jakby nie zdazyło sie zapisac przed wyswietleniem , ale za to wyrazenie przykładowo 
"./Przetwarzanie_Obrazów.out -i maly_2.pgm -n -o test -d"  działa bez problemu nie wiem z czego to wynika, wyglada to na problem z programem "display"
*/

/* TEST 17
Jeśli użytkownik korzysta z menu wczyta plik, zrobi na nim konturowanie, zapisze go pod nazwa i bedzie chcail go wysiwetlic to jest taki sam problem jak w teście 16
*/

/*WNIOSKI KOŃCOWE: POZYTYWNE, PROGRAM DZIAŁA ZGODNIE Z ZAŁOŻENIAMI, BEZ FUNKCJI OBROTU O 90 stopni dla OBRAZOW PPM*/


## Contact
Created by Marek Szulak
https://github.com/2526-MAREK
