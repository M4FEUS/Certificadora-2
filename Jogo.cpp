#include "Jogo.h"

Jogo::Jogo() {
    _numJogadores = 0;
    _numPerguntasCarregadas = 0;
    _perguntaAtualIndex = 0;
    _jogoIniciado = false;
}

void Jogo::adicionarJogador(Jogador& jogador) {
    if (_numJogadores < MAX_JOGADORES) {
        _jogadores[_numJogadores++] = &jogador;
    }
}

void Jogo::adicionarBotao(Botao& botao) {
    // Assumindo que a ordem de adição de botões corresponde à ordem de jogadores
    if (_numJogadores > 0 && _numJogadores <= MAX_JOGADORES) { // _numJogadores já foi incrementado pelo adicionarJogador
        _botoes[_numJogadores - 1] = &botao;
    }
}

void Jogo::adicionarLampada(Lampada& lampada) {
    // Assumindo que a ordem de adição de lâmpadas corresponde à ordem de jogadores
    if (_numJogadores > 0 && _numJogadores <= MAX_JOGADORES) {
        _lampadas[_numJogadores - 1] = &lampada;
    }
}

void Jogo::carregarPerguntas(Pergunta perguntas[], int numPerguntas) {
    for (int i = 0; i < numPerguntas && i < MAX_PERGUNTAS; i++) {
        _perguntas[i] = &perguntas[i];
        _numPerguntasCarregadas++;
    }
    embaralharPerguntas(); // Embaralha as perguntas ao carregar
}

void Jogo::iniciarJogo() {
    Serial.println("Iniciando Jogo Ciencia ou Consequencia!");
    Serial.println("--------------------------------------");
    for (int i = 0; i < _numJogadores; i++) {
        _jogadores[i]->resetarPontuacao();
        _lampadas[i]->apagar();
    }
    _perguntaAtualIndex = 0;
    _jogoIniciado = true;
    apresentarPerguntaAtual();
}

void Jogo::executarRodada() {
    if (!_jogoIniciado || _perguntaAtualIndex >= _numPerguntasCarregadas) {
        return; // Jogo não iniciado ou sem mais perguntas
    }

    for (int i = 0; i < _numJogadores; i++) {
        if (_botoes[i]->lerEstado()) {
            processarPressionamentoBotao(i);
            return; // Um botão foi pressionado, processa e sai do loop
        }
    }
}

void Jogo::proximaRodada() {
    _perguntaAtualIndex++;
    if (_perguntaAtualIndex < _numPerguntasCarregadas) {
        apresentarPerguntaAtual();
    } else {
        Serial.println("\nFim do Jogo! Nao ha mais perguntas.");
        for (int i = 0; i < _numJogadores; i++) {
            Serial.println(_jogadores[i]->getNome() + " pontuacao final: " + _jogadores[i]->getPontuacao());
        }
        _jogoIniciado = false;
    }
}

void Jogo::reiniciarJogo() {
    _jogoIniciado = false;
    iniciarJogo();
}

void Jogo::apresentarPerguntaAtual() {
    if (_perguntaAtualIndex < _numPerguntasCarregadas) {
        Serial.println("\nPERGUNTA: " + _perguntas[_perguntaAtualIndex]->getTexto());
        Serial.println("Pressione o botao para responder!");
    }
}

void Jogo::processarPressionamentoBotao(int jogadorIndex) {
    Serial.println(_jogadores[jogadorIndex]->getNome() + " pressionou o botao!");
    _lampadas[jogadorIndex]->acender();
    _jogadores[jogadorIndex]->adicionarPontos(1); // Exemplo: adiciona 1 ponto
    Serial.println(_jogadores[jogadorIndex]->getNome() + " pontuacao: " + _jogadores[jogadorIndex]->getPontuacao());
    delay(2000); // Espera para visualização
    _lampadas[jogadorIndex]->apagar();
    proximaRodada();
}

void Jogo::embaralharPerguntas() {
    // Implementação do algoritmo Fisher-Yates para embaralhar as perguntas
    for (int i = _numPerguntasCarregadas - 1; i > 0; i--) {
        int j = random(i + 1);
        Pergunta* temp = _perguntas[i];
        _perguntas[i] = _perguntas[j];
        _perguntas[j] = temp;
    }
}

