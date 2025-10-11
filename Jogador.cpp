#include "Jogador.h"

Jogador::Jogador(String nome) {
    _nome = nome;
    _pontuacao = 0;
}

String Jogador::getNome() {
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

