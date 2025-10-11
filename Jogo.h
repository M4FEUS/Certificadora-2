#ifndef Jogo_h
#define Jogo_h

#include <Arduino.h>
#include "Botao.h"
#include "Lampada.h"
#include "Jogador.h"
#include "Pergunta.h"

// Defina o número máximo de jogadores e perguntas aqui, ou torne dinâmico
const int MAX_JOGADORES = 2;
const int MAX_PERGUNTAS = 10; // Exemplo, pode ser carregado dinamicamente

class Jogo {
public:
    Jogo(); // Construtor padrão
    void adicionarJogador(Jogador& jogador);
    void adicionarBotao(Botao& botao);
    void adicionarLampada(Lampada& lampada);
    void carregarPerguntas(Pergunta perguntas[], int numPerguntas);
    void iniciarJogo();
    void executarRodada();
    void proximaRodada();
    void reiniciarJogo();

private:
    Jogador* _jogadores[MAX_JOGADORES];
    Botao* _botoes[MAX_JOGADORES];
    Lampada* _lampadas[MAX_JOGADORES];
    Pergunta* _perguntas[MAX_PERGUNTAS];
    int _numJogadores;
    int _numPerguntasCarregadas;
    int _perguntaAtualIndex;
    bool _jogoIniciado;

    void apresentarPerguntaAtual();
    void processarPressionamentoBotao(int jogadorIndex);
    void embaralharPerguntas();
};

#endif

