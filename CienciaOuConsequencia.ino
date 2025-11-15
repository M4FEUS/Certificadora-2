#include <LiquidCrystal_I2C.h>
#include "Botao.h"
#include "Lampada.h"
#include "Jogador.h"
#include "Pergunta.h"
#include "DisplayLCD.h"
#include "Jogo.h"

// --- Configurações do Hardware ---
// Pinos dos Jogadores
const int PINO_BOTAO_JOGADOR1 = 2;
const int PINO_LAMPADA_JOGADOR1 = 3;
const int PINO_BOTAO_JOGADOR2 = 4;
const int PINO_LAMPADA_JOGADOR2 = 5;

// Pinos do Mediador
const int PINO_BOTAO_RESET = 6;
const int PINO_BOTAO_PONTO1 = 7;
const int PINO_BOTAO_PONTO2 = 8;

// Configurações do LCD I2C
const uint8_t LCD_ADDR = 0x27; // Endereço I2C do seu LCD
const uint8_t LCD_COLS = 16;   // Colunas do LCD
const uint8_t LCD_ROWS = 2;    // Linhas do LCD

// --- Instâncias dos Objetos ---
// Componentes dos Jogadores
Botao botaoJogador1(PINO_BOTAO_JOGADOR1);
Lampada lampadaJogador1(PINO_LAMPADA_JOGADOR1);
Jogador jogador1("J1");

Botao botaoJogador2(PINO_BOTAO_JOGADOR2);
Lampada lampadaJogador2(PINO_LAMPADA_JOGADOR2);
Jogador jogador2("J2");

// Componentes do Mediador
Botao botaoReset(PINO_BOTAO_RESET);
Botao botaoPonto1(PINO_BOTAO_PONTO1);
Botao botaoPonto2(PINO_BOTAO_PONTO2);

// Display LCD
DisplayLCD display(LCD_ADDR, LCD_COLS, LCD_ROWS);

// Instância principal do Jogo
Jogo meuJogo(display);

// Banco de Perguntas
Pergunta perguntas[] = {
    Pergunta("Qual a capital do Brasil?", "Brasilia"),
    Pergunta("Qual o maior planeta do sistema solar?", "Jupiter"),
    Pergunta("Quem descobriu o Brasil?", "Pedro Alvares Cabral"),
    Pergunta("Formula da agua?", "H2O"),
    Pergunta("Qual a cor do cavalo branco de Napoleao?", "Branco")
};
const int NUM_PERGUNTAS = sizeof(perguntas) / sizeof(perguntas[0]);

void setup() {
    Serial.begin(9600);
    randomSeed(analogRead(0)); // Semente para números aleatórios

    // Inicia o display LCD
    display.iniciar();

    // Adiciona os jogadores e seus componentes ao jogo
    meuJogo.adicionarJogador(jogador1, botaoJogador1, lampadaJogador1);
    meuJogo.adicionarJogador(jogador2, botaoJogador2, lampadaJogador2);

    // Adiciona os botões de controle do mediador
    meuJogo.adicionarBotoesMediador(botaoReset, botaoPonto1, botaoPonto2);

    // Carrega o banco de perguntas
    meuJogo.carregarPerguntas(perguntas, NUM_PERGUNTAS);

    // Inicia o jogo (o jogo começará no estado FIM_DE_JOGO, aguardando o reset)
    // Pressione o botão de reset para começar a primeira partida.
    display.escrever("Pressione RESET", 0, 0);
    display.escrever("para comecar!", 0, 1);
}

void loop() {
    // O método executar agora contém toda a máquina de estados do jogo
    meuJogo.executar();
}