#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pso.h"
#include "obsluga_map.h"
#include "logger.h"

int main(int argc, char** argv) {
    const char* mapa_file = (argc > 1) ? argv[1] : "test_map.txt";
    const char* log_file = "log.csv";

    srand((unsigned)time(NULL));

    Mapa* mapa = wczytaj_mape(mapa_file);
    if (mapa == NULL) {
        fprintf(stderr, "Nie mozna wczytac mapy %s\n", mapa_file);
        return 1;
    }

    inicjalizuj_logger(log_file);

    Roj roj;
    int liczba_czastek = 30;
    int iteracje = 100;
    double waga = 0.5, c1 = 1.0, c2 = 1.0;

    inicjalizuj_roj(&roj, liczba_czastek, mapa->szerokosc, mapa->wysokosc, mapa);

    zapisz_stan_roju(log_file, 0, &roj);

    for (int it = 1; it <= iteracje; it++) {
        aktualizuj_roj(&roj, waga, c1, c2, mapa);
        zapisz_stan_roju(log_file, it, &roj);
    }

    free(roj.czasteczki);
    usun_mape(mapa);

    printf("Symulacja zakonczona. Log w %s\n", log_file);
    return 0;
}
