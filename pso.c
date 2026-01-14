
#include <stdlib.h>
#include <math.h>
#include "pso.h"
#include <stddef.h>
/* Forward-declare random helpers from narzedzia_pomocznicze.c to avoid include ordering issues */
double random_double();
double random_w_zakresie(double min, double max);


void inicjalizuj_roj(Roj *r, int liczba_czasteczek, int maxX, int maxY, const Mapa* mapa) {
    r->liczba_czasteczek = liczba_czasteczek;
    r->czasteczki = (Czasteczka*) malloc(liczba_czasteczek * sizeof(Czasteczka));

    r->najlepsza_globalna_wartosc = -1e9;
    r->najlepsze_globalne_x = 0;
    r->najlepsze_globalne_y = 0;

    for (int i = 0; i < liczba_czasteczek; i++) {
        Czasteczka *c = &r->czasteczki[i];
        c->id = i;

        c->x = random_w_zakresie(0.0, (double)(maxX - 1));
        c->y = random_w_zakresie(0.0, (double)(maxY - 1));

        c->vx = (random_double() * 2.0 - 1.0) * (maxX * 0.1);
        c->vy = (random_double() * 2.0 - 1.0) * (maxY * 0.1);

        c->najlepsze_x = c->x;
        c->najlepsze_y = c->y;

        int ix = (int)round(c->x);
        int iy = (int)round(c->y);

        c->najlepsza_wartosc = pobierz_wartosc(mapa, ix, iy);

        if (c->najlepsza_wartosc > r->najlepsza_globalna_wartosc) {
            r->najlepsza_globalna_wartosc = c->najlepsza_wartosc;
            r->najlepsze_globalne_x = c->x;
            r->najlepsze_globalne_y = c->y;
        }
    }
}

void aktualizuj_roj(Roj *r, double waga, double c1, double c2, const Mapa* mapa) {
    for (int i = 0; i < r->liczba_czasteczek; i++) {
        Czasteczka *c = &r->czasteczki[i];

        double los1 = random_double();
        double los2 = random_double();

        c->vx = waga * c->vx
              + c1 * los1 * (c->najlepsze_x - c->x)
              + c2 * los2 * (r->najlepsze_globalne_x - c->x);

        c->vy = waga * c->vy
              + c1 * los1 * (c->najlepsze_y - c->y)
              + c2 * los2 * (r->najlepsze_globalne_y - c->y);

        c->x += c->vx;
        c->y += c->vy;

        /* boundary handling: reflect with damping when hitting map edges */
        if (c->x < 0.0) {
            c->x = 0.0;
            c->vx = -c->vx * 0.5;
        } else if (c->x > (mapa->szerokosc - 1)) {
            c->x = (double)(mapa->szerokosc - 1);
            c->vx = -c->vx * 0.5;
        }

        if (c->y < 0.0) {
            c->y = 0.0;
            c->vy = -c->vy * 0.5;
        } else if (c->y > (mapa->wysokosc - 1)) {
            c->y = (double)(mapa->wysokosc - 1);
            c->vy = -c->vy * 0.5;
        }

        int ix = (int)round(c->x);
        int iy = (int)round(c->y);
        double wartosc = pobierz_wartosc(mapa, ix, iy);

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
