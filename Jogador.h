#ifndef Jogador_h
#define Jogador_h

#include <Arduino.h>

class Jogador {
public:
    Jogador(const char* nome);
    const char* getNome();
    int getPontuacao();
    void adicionarPontos(int pontos);
    void resetarPontuacao();

private:
    char _nome[16]; // Tamanho fixo para economizar memória
    int _pontuacao;
};

#endif

