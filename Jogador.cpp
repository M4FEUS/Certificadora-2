#include "Jogador.h"
#include <string.h>

Jogador::Jogador(const char* nome) {
    strncpy(_nome, nome, 15);
    _nome[15] = '\0';
    _pontuacao = 0;
}

const char* Jogador::getNome() {
    return _nome;
}

int Jogador::getPontuacao() {
    return _pontuacao;
}

void Jogador::adicionarPontos(int pontos) {
    _pontuacao += pontos;
}

void Jogador::resetarPontuacao() {
    _pontuacao = 0;
}

