#include "Lampada.h"

Lampada::Lampada(int pino) {
    _pino = pino;
    pinMode(_pino, OUTPUT);
    _estado = false; // Começa apagada
    digitalWrite(_pino, LOW);
}

void Lampada::acender() {
    digitalWrite(_pino, HIGH);
    _estado = true;
}

void Lampada::apagar() {
    digitalWrite(_pino, LOW);
    _estado = false;
}

bool Lampada::estaAcesa() {
    return _estado;
}

