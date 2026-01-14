#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"


void inicjalizuj_logger(const char* nazwa_pliku);

void zapisz_stan_roju(const char* nazwa_pliku, int iteracja, Roj* roj);

#endif