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
