#ifndef Jogador_h
#define Jogador_h

#include <Arduino.h>

class Jogador {
public:
    Jogador(String nome);
    String getNome();
    int getPontuacao();
    void adicionarPontos(int pontos);
    void resetarPontuacao();

private:
    String _nome;
    int _pontuacao;
};

#endif

