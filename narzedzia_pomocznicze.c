#include "narzedzia_pomocznicze.h"
#include <time.h>

double random_double() {
    return (double)rand() / (double)RAND_MAX;
}

double random_w_zakresie(double min, double max) {
    return min + random_double() * (max - min);
}