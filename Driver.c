#include "Surucu.h"

void surucu(Surucu* s, unsigned int state) {
    s->state = state;
}

unsigned int surucuDurum(Surucu* s) {
    return s->state;
}