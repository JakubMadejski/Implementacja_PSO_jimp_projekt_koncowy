#ifndef PSO_H
#define PSO_H

typedef struct {
    int id;
    double x, y;
    double vx, vy;
    double najlepsze_x, najlepsze_y;
    double najlepsza_wartosc;
} Cząsteczka;

typedef struct {
    Cząsteczka *cząsteczki;
    int liczba_cząsteczek;
    double najlepsze_globalne_x, najlepsze_globalne_y;
    double najlepsza_globalna_wartosc;
} Rój;

void inicjalizuj_roj(Rój *r, int liczba_cząsteczek, int maxX, int maxY);
void aktualizuj_roj(Rój *r, double waga, double c1, double c2);

#endif
