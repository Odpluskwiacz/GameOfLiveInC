#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIERSZE 40
#define KOLUMNY 60

int plansza[WIERSZE][KOLUMNY];

void inicjalizujPlansze() {
    for (int i = 0; i < WIERSZE; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            plansza[i][j] = rand() % 2; // GENERUJ DLA DANEJ [I][J] LICZBĘ 0 LUB 1
        }
    }
}

void drukujPlansze() {
    system("clear"); // Czyszczenie konsoli (dla systemów Unix) POZBYWAM SIE "podaj ilość generacji :" I STAREJ PLANSZYS
    for (int i = 0; i < WIERSZE; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            printf("%c ", (plansza[i][j] == 1) ? '@' : '`');
        }
        printf("\n");
    }
    usleep(100000); // Czas snu 100,000 mikrosekund (0.1 sekundy) INACZEJ WSZYSTKO DZIEJE SIE W 0.00000000000001 SEKUNDY
}

int liczSasiadow(int wiersz, int kolumna) {
    int liczbaSasiadow = 0;
    for (int i = wiersz - 1; i <= wiersz + 1; ++i) {	//wyżej środek prawa dla [i][j]
        for (int j = kolumna - 1; j <= kolumna + 1; ++j) {  //lewa środek prawa dla [i][j]
            if (i >= 0 && i < WIERSZE && j >= 0 && j < KOLUMNY && !(i == wiersz && j == kolumna)) {  //sprawdza czy nie wypadło poza WIERSZ I KOLUMNE + czy nie liczy samej siebie np.WIERSZ == wiersz 
                liczbaSasiadow += plansza[i][j]; // jezel if(x) prawdziwe to zwiększamy liczbe sasiadow dla danej planysz [i][j]
            }
        }
    }
    return liczbaSasiadow;
}

void aktualizujPlansze() {
    int nowaPlansza[WIERSZE][KOLUMNY];

    for (int i = 0; i < WIERSZE; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            int sasiedzi = liczSasiadow(i, j);

            if (plansza[i][j] == 1) {
                // Komórka żyje
                if (sasiedzi < 2 || sasiedzi > 3) {
                    nowaPlansza[i][j] = 0; // Umiera z powodu zbyt małej lub zbyt dużej liczby sąsiadów
                } else {
                    nowaPlansza[i][j] = 1; // Żyje dalej
                }
            } else {
                // Komórka martwa
                if (sasiedzi == 3) {
                    nowaPlansza[i][j] = 1; // Ożywa z powodu reprodukcji
                } else {
                    nowaPlansza[i][j] = 0; // Pozostaje martwa
                }
            }
        }
    }

    // Kopiuj nowaPlansza do plansza
    for (int i = 0; i < WIERSZE; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            plansza[i][j] = nowaPlansza[i][j];
        }
    }
}

int main() {
	int IloscGeneracji;
	printf("podaj ilość generacji: ");
	scanf("%d", &IloscGeneracji);
    inicjalizujPlansze();

    for (int generacja = 0; generacja < IloscGeneracji; ++generacja) {
        drukujPlansze();
        aktualizujPlansze();
    }

    return 0;
}

