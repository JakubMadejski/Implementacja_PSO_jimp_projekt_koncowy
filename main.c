#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "pso.h"
#include "obsluga_map.h"
#include "logger.h"


static void wczytaj_config(const char* nazwa, double* waga, double* c1, double* c2) {
    if (nazwa == NULL) return;
    FILE* f = fopen(nazwa, "r");
    if (f == NULL) return;
    if (fscanf(f, "%lf %lf %lf", waga, c1, c2) != 3) {
    }
    fclose(f);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Uzycie: %s <plik_mapy> -p <liczba_czasteczek> -i <liczba_iteracji> -c <plik_konfig> -n <co_n>\n", argv[0]);
        return 1;
    }

    const char* mapa_file = argv[1];
    int liczba_czasteczek = 30;
    int iteracje = 100;
    const char* config_file = NULL;
    int zapisz_co_n = 1;
    const char* log_file = "log.csv";

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            liczba_czasteczek = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            iteracje = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            config_file = argv[++i];
        } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            zapisz_co_n = atoi(argv[++i]);
            if (zapisz_co_n <= 0) zapisz_co_n = 1;
        } else {
            fprintf(stderr, "Nieznana flaga lub brak argumentu: %s\n", argv[i]);
            return 1;
        }
    }

    double waga = 0.5, c1 = 1.0, c2 = 1.0;
    wczytaj_config(config_file, &waga, &c1, &c2);

    srand((unsigned)time(NULL));

    Mapa* mapa = wczytaj_mape(mapa_file);
    if (mapa == NULL) {
        fprintf(stderr, "Nie mozna wczytac mapy %s\n", mapa_file);
        return 1;
    }

    inicjalizuj_logger(log_file);

    Roj roj;

    inicjalizuj_roj(&roj, liczba_czasteczek, mapa->szerokosc, mapa->wysokosc, mapa);

    zapisz_stan_roju(log_file, 0, &roj);

    for (int it = 1; it <= iteracje; it++) {
        aktualizuj_roj(&roj, waga, c1, c2, mapa);
        if (zapisz_co_n > 0 && (it % zapisz_co_n) == 0) {
            zapisz_stan_roju(log_file, it, &roj);
        }
    }

    free(roj.czasteczki);
    usun_mape(mapa);

    printf("Symulacja zakonczona. Log w %s\n", log_file);
    return 0;
}
