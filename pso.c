#include <stdlib.h>
#include <math.h>
#include "pso.h"
#include "utils.h"
#include "obsluga_map.h"

void inicjalizuj_roj(Rój *r, int liczba_cząsteczek, int maxX, int maxY) {
    r->liczba_cząsteczek = liczba_cząsteczek;
    r->cząsteczki = (Cząsteczka*) malloc(liczba_cząsteczek * sizeof(Cząsteczka));

    r->najlepsza_globalna_wartosc = -1e9;
    r->najlepsze_globalne_x = 0;
    r->najlepsze_globalne_y = 0;

    for (int i = 0; i < liczba_cząsteczek; i++) {
        Cząsteczka *c = &r->cząsteczki[i];
        c->id = i;

        c->x = random_range(0, maxX - 1);
        c->y = random_range(0, maxY - 1);

        c->vx = random_range(-1, 1) * (maxX * 0.1);
        c->vy = random_range(-1, 1) * (maxY * 0.1);

        c->najlepsze_x = c->x;
        c->najlepsze_y = c->y;

        int ix = (int)round(c->x);
        int iy = (int)round(c->y);

        c->najlepsza_wartosc = pobierz_wartosc(ix, iy);

        if (c->najlepsza_wartosc > r->najlepsza_globalna_wartosc) {
            r->najlepsza_globalna_wartosc = c->najlepsza_wartosc;
            r->najlepsze_globalne_x = c->x;
            r->najlepsze_globalne_y = c->y;
        }
    }
}

void aktualizuj_roj(Rój *r, double waga, double c1, double c2) {
    for (int i = 0; i < r->liczba_cząsteczek; i++) {
        Cząsteczka *c = &r->cząsteczki[i];

        double los1 = random_0_1();
        double los2 = random_0_1();

        c->vx = waga * c->vx
              + c1 * los1 * (c->najlepsze_x - c->x)
              + c2 * los2 * (r->najlepsze_globalne_x - c->x);

        c->vy = waga * c->vy
              + c1 * los1 * (c->najlepsze_y - c->y)
              + c2 * los2 * (r->najlepsze_globalne_y - c->y);

        c->x += c->vx;
        c->y += c->vy;

        int ix = (int)round(c->x);
        int iy = (int)round(c->y);
        double wartosc = pobierz_wartosc(ix, iy);

        if (wartosc > c->najlepsza_wartosc) {
            c->najlepsza_wartosc = wartosc;
            c->najlepsze_x = c->x;
            c->najlepsze_y = c->y;
        }

        if (wartosc > r->najlepsza_globalna_wartosc) {
            r->najlepsza_globalna_wartosc = wartosc;
            r->najlepsze_globalne_x = c->x;
            r->najlepsze_globalne_y = c->y;
        }
    }
}
