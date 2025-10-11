#include "Botao.h"
#include "Lampada.h"
#include "Jogador.h"
#include "Pergunta.h"
#include "Jogo.h"

// Definição dos pinos
const int PINO_BOTAO_JOGADOR1 = 2;
const int PINO_LAMPADA_JOGADOR1 = 3;
const int PINO_BOTAO_JOGADOR2 = 4;
const int PINO_LAMPADA_JOGADOR2 = 5;

// Instâncias dos objetos de componentes e jogadores
Botao botaoJogador1(PINO_BOTAO_JOGADOR1);
Lampada lampadaJogador1(PINO_LAMPADA_JOGADOR1);
Jogador jogador1("Jogador 1");

Botao botaoJogador2(PINO_BOTAO_JOGADOR2);
Lampada lampadaJogador2(PINO_LAMPADA_JOGADOR2);
Jogador jogador2("Jogador 2");

// Instância da classe Jogo
Jogo meuJogo;

// Estrutura de dados para armazenar perguntas
// Em um projeto mais avançado, isso poderia ser um vetor dinâmico ou carregado de SD
Pergunta perguntas[] = {
    Pergunta("Qual a capital do Brasil?", "Brasilia"),
    Pergunta("Qual o maior planeta do sistema solar?", "Jupiter"),
    Pergunta("Quem descobriu o Brasil?", "Pedro Alvares Cabral")
};
const int NUM_PERGUNTAS = sizeof(perguntas) / sizeof(perguntas[0]);

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0)); // Inicializa o gerador de números aleatórios

    // Adiciona jogadores, botões e lâmpadas ao objeto Jogo
    meuJogo.adicionarJogador(jogador1);
    meuJogo.adicionarBotao(botaoJogador1);
    meuJogo.adicionarLampada(lampadaJogador1);

    meuJogo.adicionarJogador(jogador2);
    meuJogo.adicionarBotao(botaoJogador2);
    meuJogo.adicionarLampada(lampadaJogador2);

    // Carrega as perguntas no objeto Jogo
    meuJogo.carregarPerguntas(perguntas, NUM_PERGUNTAS);

    // Inicia o jogo
    meuJogo.iniciarJogo();
}

void loop() {
    meuJogo.executarRodada();
}

