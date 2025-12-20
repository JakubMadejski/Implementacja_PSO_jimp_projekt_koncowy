#ifndef OBSLUGA_MAP_H
#define OBSLUGA_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int szerokosc;
    int wysokosc;
    double *dane;
} Mapa;

Mapa* wczytaj_mape(const char* nazwa_pliku);

void usun_mape(Mapa* mapa);

double pobierz_wartosc(const Mapa* mapa, int x, int y);

#endif // OBSLUGA_MAP_H