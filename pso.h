#ifndef PSO_H
#define PSO_H

#include "obsluga_map.h"

typedef struct Czasteczka {
    int id;
    double x, y;
    double vx, vy;
    double najlepsze_x, najlepsze_y;
    double najlepsza_wartosc;
} Czasteczka;

typedef struct Roj {
    Czasteczka *czasteczki;
    int liczba_czasteczek;
    double najlepsze_globalne_x, najlepsze_globalne_y;
    double najlepsza_globalna_wartosc;
} Roj;

void inicjalizuj_roj(Roj *r, int liczba_czasteczek, int maxX, int maxY, const Mapa* mapa);
void aktualizuj_roj(Roj *r, double waga, double c1, double c2, const Mapa* mapa);

#endif
