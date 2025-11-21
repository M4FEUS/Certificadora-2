#include <LiquidCrystal.h> // Biblioteca para LCD padrão
#include <avr/pgmspace.h>
#include "DisplayLCD.h"
#include "Jogo.h"
#include "Jogador.h"
#include "Botao.h"
#include "Lampada.h"
#include "Pergunta.h"

// --- Configuração do LCD (Modo 4 bits) ---
// RS=12, E=11, D4=10, D5=9, D6=A1, D7=A2
DisplayLCD display(7, 6, 5, 4, 3, 2);

// --- Pinos do Hardware ---
// Jogador 1
const int PINO_BOTAO_J1 = 10;
const int PINO_LAMPADA_J1 = 12;

// Jogador 2
const int PINO_BOTAO_J2 = 11;
const int PINO_LAMPADA_J2 = 9;

// Botões do Mediador (Pontuação)
const int PINO_BOTAO_PONTO_J1 = A5;  // Botão para pontuar Jogador 1
const int PINO_BOTAO_PONTO_J2 = A4;  // Botão para pontuar Jogador 2

// Potenciômetro de Dificuldade
const int PINO_POTENCIOMETRO = A0; 

// --- Objetos Globais ---
Jogo meuJogo(display);
Jogador jogador1("Jogador 1");
Botao botaoJ1(PINO_BOTAO_J1);
Lampada lampadaJ1(PINO_LAMPADA_J1);

Jogador jogador2("Jogador 2");
Botao botaoJ2(PINO_BOTAO_J2);
Lampada lampadaJ2(PINO_LAMPADA_J2);

// Botões do Mediador
Botao botaoPontoJ1(PINO_BOTAO_PONTO_J1);
Botao botaoPontoJ2(PINO_BOTAO_PONTO_J2);

// ==========================================================================
// BANCO DE PERGUNTAS (Colados do seu arquivo) - Usando PROGMEM
// ==========================================================================

// --- NÍVEL FÁCIL ---
const char perguntasFaceis_texto[][60] PROGMEM = {
    "Qual peixe e o Bolhas de Procurando Nemo?",
    "Cor do papa-leguas?",
    "Manny da Era do Gelo e um?",
    "Formato da Terra?",
    "Dory e qual peixe?",
    "Lula Molusco e um?",
    "Fases da Lua sao?",
    "Nome do Sal de Cozinha?",
    "Estrelas no Cruzeiro do Sul?",
    "Minutos em 3 horas?",
    "Coracoes de um polvo?",
    "Ave bate asa 200x/seg?"
};
const char perguntasFaceis_resposta[] PROGMEM = {'b','c','b','b','b','b','a','b','c','d','c','d'};

// --- NÍVEL MÉDIO ---
const char perguntasMedias_texto[][60] PROGMEM = {
    "Planeta mais quente?",
    "Microondas faz mal?",
    "Frase sobre vida fora da Terra?",
    "Elementos na tabela periodica?",
    "Acido de bateria de carro?",
    "Gas do refrigerante?",
    "Menor e maior pais?",
    "Animal que amamentou Romulo?",
    "Oceano de Madagascar?",
    "Orgaos respiratorios?",
    "Ossos no corpo adulto?",
    "Monumento inclinado?",
    "Ano-luz mede?",
    "Ar condicionado no alto?",
    "Por que a lua brilha?",
    "Seculos em um milenio?",
    "Energia eolica vem de?",
    "Dentes de adulto?",
    "Pais com maior extensao?",
    "Primeiro caso COVID-19?",
    "Nao faz fronteira com Brasil?"
};
const char perguntasMedias_resposta[] PROGMEM = {'b','c','b','a','b','d','c','d','c','d','d','a','b','d','d','a','c','b','d','c','d'};

// --- NÍVEL DIFÍCIL ---
const char perguntasDificeis_texto[][60] PROGMEM = {
    "Nao existe macho alfa?",
    "Maior proteina?",
    "Beneficios Sal quantico?",
    "Frase beleza da ciencia?",
    "Elemento base organica?",
    "Elemento abundante universo?",
    "Lei do 'pum' nos empurra?",
    "Traducao de Legend?",
    "Apenas classes gramaticais?",
    "Descobriu pasteurizacao?",
    "Corrente eletrica e?",
    "Garrafa explode no freezer?",
    "Anos em 2 seculos e meio?",
    "Idiomas do Canada?",
    "Duracao Guerra 100 anos?",
    "Cidades bombas atomicas?",
    "Cm em 1 metro e meio?"
};
const char perguntasDificeis_resposta[] PROGMEM = {'a','b','c','a','c','d','a','b','b','a','a','c','a','b','a','b','b'};

// Array único de perguntas (reutilizado)
Pergunta perguntas[21]; // Tamanho do maior array

void setup() {
    Serial.begin(9600);
    
    // Inicializa o LCD
    display.iniciar();
    display.limpar();
    display.escrever(F("Iniciando..."), 0, 0);

    // Semente aleatória (Usando A3 pois A0, A1 e A2 estão ocupados)
    randomSeed(analogRead(A3)); 

    Serial.println(F("Bem-vindo ao Ciencia ou Consequencia!"));

    // Configuração do Jogo
    meuJogo.adicionarJogador(jogador1, botaoJ1, lampadaJ1);
    meuJogo.adicionarJogador(jogador2, botaoJ2, lampadaJ2);
    
    // Configuração dos botões do mediador (pontuação)
    meuJogo.adicionarBotoesMediador(botaoPontoJ1, botaoPontoJ2);

    // --- Leitura da Dificuldade ---
    display.limpar();
    display.escrever(F("Selecione Nivel"), 0, 0);
    delay(3000); // Tempo para o usuário girar o potenciômetro (3 segundos)

    int valorPot = analogRead(PINO_POTENCIOMETRO);
    
    // Debug: mostra o valor lido no Serial
    Serial.print(F("Valor do potenciometro: "));
    Serial.println(valorPot);
    
    // Se o potenciômetro não estiver conectado (valor muito próximo de 0 ou 1023),
    // usa o nível MÉDIO como padrão
    // Ajustado para ser menos restritivo - só força médio se realmente desconectado
    if (valorPot <= 5 || valorPot >= 1020) {
        // Potenciômetro provavelmente desconectado, usa padrão MÉDIO
        Serial.println(F("Potenciometro desconectado, usando MEDIO"));
        valorPot = 500; // Valor médio para forçar nível MÉDIO
    }
    
    if (valorPot < 341) { 
        Serial.println(F("Dificuldade: FACIL"));
        display.escrever(F("Nivel: FACIL"), 0, 1);
        // Inicializa perguntas fáceis
        for (int i = 0; i < 12; i++) {
            char resposta = pgm_read_byte(&perguntasFaceis_resposta[i]);
            perguntas[i] = Pergunta(perguntasFaceis_texto[i], resposta);
        }
        meuJogo.carregarPerguntas(perguntas, 12);

    } else if (valorPot < 682) { 
        Serial.println(F("Dificuldade: MEDIO"));
        display.escrever(F("Nivel: MEDIO"), 0, 1);
        // Inicializa perguntas médias
        for (int i = 0; i < 21; i++) {
            char resposta = pgm_read_byte(&perguntasMedias_resposta[i]);
            perguntas[i] = Pergunta(perguntasMedias_texto[i], resposta);
        }
        meuJogo.carregarPerguntas(perguntas, 21);

    } else { 
        Serial.println(F("Dificuldade: DIFICIL"));
        display.escrever(F("Nivel: DIFICIL"), 0, 1);
        // Inicializa perguntas difíceis
        for (int i = 0; i < 17; i++) {
            char resposta = pgm_read_byte(&perguntasDificeis_resposta[i]);
            perguntas[i] = Pergunta(perguntasDificeis_texto[i], resposta);
        }
        meuJogo.carregarPerguntas(perguntas, 17);
    }
    
    delay(2000); // Espera 2 segundos para ler o nível na tela
    display.limpar();
    
    // Inicia o jogo
    meuJogo.iniciarJogo();
}

void loop() {
    meuJogo.executar();
}