#include "logger.h"
#include <stdio.h>

void inicjalizuj_logger(const char* nazwa_pliku) {
    FILE* plik = fopen(nazwa_pliku, "w");
    if (plik == NULL) {
        perror("Ostrzeżenie: Nie można utworzyć pliku logów");
        return;
    }
    fprintf(plik, "Iteracja,ID_Czastki,X,Y,Wartosc,pBestVal\n");
    fclose(plik);
}

void zapisz_stan_roju(const char* nazwa_pliku, int iteracja, Roj* roj) {

    if (roj == NULL) return;

    FILE* plik = fopen(nazwa_pliku, "a");
    if (plik == NULL) {
        perror("Ostrzeżenie: Nie można otworzyć pliku logów do zapisu");
        return;
    }

    for (int i = 0; i < roj->liczba_czasteczek; i++) {
        Czasteczka* c = &roj->czasteczki[i];
        fprintf(plik, "%d,%d,%.6f,%.6f,%.6f,%.6f\n",
                iteracja,
                c->id,
                c->x,
                c->y,
                c->najlepsza_wartosc,
                roj->najlepsza_globalna_wartosc);
    }

    fclose(plik);
}
