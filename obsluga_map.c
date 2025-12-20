#include "obsluga_map.h"

Mapa* wczytaj_mape(const char* nazwa_pliku) {
    FILE* plik = fopen(nazwa_pliku, "r");
    if (plik == NULL) {
        perror("Nie mozna otworzyc pliku");
        return NULL;
    }

    int szerokosc, wysokosc;
    if (fscanf(plik, "%d %d", &szerokosc, &wysokosc) != 2) {
        fprintf(stderr, "Blad nie mozna otworzyc pliku %s\n", nazwa_pliku);
        fclose(plik);
        return NULL;
    }

    Mapa* wczytana_mapa = (Mapa*)malloc(sizeof(Mapa));
    if (wczytana_mapa == NULL) {
        fclose(plik);
        return NULL;
    }

    wczytana_mapa->szerokosc = szerokosc;
    wczytana_mapa->wysokosc = wysokosc;
    wczytana_mapa->dane = (double*)malloc(szerokosc * wysokosc * sizeof(double));
    if (wczytana_mapa->dane == NULL) {
        free(wczytana_mapa);
        fclose(plik);
        return NULL;
    }

    for (int i = 0; i < wysokosc * szerokosc; i++) {
        if (fscanf(plik, "%lf", &wczytana_mapa->dane[i]) != 1) {
            break;
        }
    }

    fclose(plik);
    return wczytana_mapa;
}

void usun_mape(Mapa* mapa) {
    if (mapa != NULL) {
        free(mapa->dane);
        free(mapa);
    }
}

