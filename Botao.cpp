#include "Botao.h"

Botao::Botao(int pino) {
    _pino = pino;
    pinMode(_pino, INPUT_PULLUP); // Usar pull-up interno para botões
    _estadoAnterior = digitalRead(_pino);
    _tempoInicializacao = millis();
}

bool Botao::lerEstado() {
    // Ignora leituras durante o período de aquecimento após inicialização
    // Isso evita detecções falsas causadas por ruído/flutuação na inicialização
    if (millis() - _tempoInicializacao < TEMPO_AQUECIMENTO) {
        // Durante o aquecimento, apenas atualiza o estado anterior sem retornar true
        _estadoAnterior = digitalRead(_pino);
        return false;
    }
    
    bool estadoAtual = digitalRead(_pino);
    if (estadoAtual != _estadoAnterior) {
        _estadoAnterior = estadoAtual;
        if (estadoAtual == LOW) { // Botão pressionado (LOW devido ao pull-up)
            return true;
        }
    }
    return false;
}

