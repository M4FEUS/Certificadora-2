#ifndef Jogo_h
#define Jogo_h

#include <Arduino.h>
#include "Botao.h"
#include "Lampada.h"
#include "Jogador.h"
#include "Pergunta.h"
#include "DisplayLCD.h"

// Defina o número máximo de jogadores e perguntas aqui, ou torne dinâmico
const int MAX_JOGADORES = 2;
const int MAX_PERGUNTAS = 10; // Exemplo, pode ser carregado dinamicamente

enum EstadoJogo {
    APRESENTANDO_PERGUNTA,
    AGUARDANDO_RESPOSTA_JOGADOR,
    AGUARDANDO_PONTUACAO_MEDIADOR,
    MOSTRANDO_PONTUACAO,
    FIM_DE_JOGO
};

class Jogo {
public:
    Jogo(DisplayLCD& display);
    void adicionarJogador(Jogador& jogador, Botao& botaoResposta, Lampada& lampada);
    void adicionarBotoesMediador(Botao& botaoReset, Botao& botaoPonto1, Botao& botaoPonto2);
    void carregarPerguntas(Pergunta perguntas[], int numPerguntas);
    void iniciarJogo();
    void executar();

private:
    DisplayLCD& _display;
    Jogador* _jogadores[MAX_JOGADORES];
    Botao* _botoesResposta[MAX_JOGADORES];
    Lampada* _lampadas[MAX_JOGADORES];
    Botao* _botaoReset;
    Botao* _botoesPonto[MAX_JOGADORES];
    Pergunta* _perguntas[MAX_PERGUNTAS];
    int _numJogadores;
    int _numPerguntasCarregadas;
    int _perguntaAtualIndex;
    EstadoJogo _estado;
    int _jogadorQueRespondeu;
    unsigned long _tempoDaUltimaAcao;

    void mudarEstado(EstadoJogo novoEstado);
    void apresentarPergunta();
    void aguardarRespostaJogador();
    void aguardarPontuacaoMediador();
    void mostrarPontuacao();
    void reiniciarJogo();
    void embaralharPerguntas();
};

#endif

