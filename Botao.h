#ifndef Botao_h
#define Botao_h

#include <Arduino.h>

class Botao {
public:
    Botao(int pino);
    bool lerEstado();

private:
    int _pino;
    bool _estadoAnterior;
    unsigned long _tempoInicializacao;
    static const unsigned long TEMPO_AQUECIMENTO = 200; // 200ms após inicialização
};

#endif

