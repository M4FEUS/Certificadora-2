#include "Botao.h"

Botao::Botao(int pino) {
    _pino = pino;
    pinMode(_pino, INPUT_PULLUP); // Usar pull-up interno para botões
    _estadoAnterior = digitalRead(_pino);
}

bool Botao::lerEstado() {
    bool estadoAtual = digitalRead(_pino);
    if (estadoAtual != _estadoAnterior) {
        _estadoAnterior = estadoAtual;
        if (estadoAtual == LOW) { // Botão pressionado (LOW devido ao pull-up)
            return true;
        }
    }
    return false;
}

