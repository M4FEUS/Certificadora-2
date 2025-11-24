#include "Jogo.h"

// Tempo de exibição da pontuação em milissegundos
const unsigned long TEMPO_MOSTRAR_PONTUACAO = 5000;

Jogo::Jogo(DisplayLCD& display) : _display(display) {
    _numJogadores = 0;
    _numPerguntasCarregadas = 0;
    _perguntaAtualIndex = 0;
    _jogadorQueRespondeu = -1;
    _tempoDaUltimaAcao = 0;
    _botaoReset = nullptr;
    // Inicializa os botões de pontuação como nullptr
    for (int i = 0; i < MAX_JOGADORES; i++) {
        _botoesPonto[i] = nullptr;
    }
    mudarEstado(FIM_DE_JOGO);
}

void Jogo::adicionarJogador(Jogador& jogador, Botao& botaoResposta, Lampada& lampada) {
    if (_numJogadores < MAX_JOGADORES) {
        _jogadores[_numJogadores] = &jogador;
        _botoesResposta[_numJogadores] = &botaoResposta;
        _lampadas[_numJogadores] = &lampada;
        _numJogadores++;
    }
}

void Jogo::adicionarBotoesMediador(Botao& botaoPonto1, Botao& botaoPonto2) {
    _botoesPonto[0] = &botaoPonto1;
    _botoesPonto[1] = &botaoPonto2;
}

void Jogo::carregarPerguntas(Pergunta perguntas[], int numPerguntas) {
    _numPerguntasCarregadas = 0;
    for (int i = 0; i < numPerguntas && i < MAX_PERGUNTAS; i++) {
        _perguntas[i] = &perguntas[i];
        _numPerguntasCarregadas++;
    }
    embaralharPerguntas(); // Embaralha as perguntas ao carregar
}

void Jogo::iniciarJogo() {
    Serial.println(F("Iniciando Jogo Ciencia ou Consequencia!"));
    _display.limpar();
    _display.escrever(F("Ciencia ou"), 0, 0);
    _display.escrever(F("Consequencia!"), 0, 1);
    delay(2000);

    for (int i = 0; i < _numJogadores; i++) {
        _jogadores[i]->resetarPontuacao();
        _lampadas[i]->apagar();
    }
    _perguntaAtualIndex = 0;
    mudarEstado(APRESENTANDO_PERGUNTA);
}

void Jogo::executar() {
    // Lógica de Reset Global
    if (_botaoReset != nullptr && _botaoReset->lerEstado()) {
        iniciarJogo();
        return;
    }

    switch (_estado) {
        case APRESENTANDO_PERGUNTA:
            apresentarPergunta();
            break;
        case AGUARDANDO_RESPOSTA_JOGADOR:
            aguardarRespostaJogador();
            break;
        case AGUARDANDO_PONTUACAO_MEDIADOR:
            aguardarPontuacaoMediador();
            break;
        case MOSTRANDO_PONTUACAO:
            mostrarPontuacao();
            break;
        case FIM_DE_JOGO:
            // O jogo fica parado, esperando o botão de reset
            break;
    }
}

void Jogo::mudarEstado(EstadoJogo novoEstado) {
    _estado = novoEstado;
    _tempoDaUltimaAcao = millis();
    _display.limpar();
    Serial.print("Novo Estado: ");
    Serial.println(novoEstado);

    if (novoEstado == APRESENTANDO_PERGUNTA) {
        if (_perguntaAtualIndex < _numPerguntasCarregadas) {
            apresentarPergunta();
            mudarEstado(AGUARDANDO_RESPOSTA_JOGADOR);
        } else {
            mudarEstado(FIM_DE_JOGO);
            _display.escrever(F("FIM DE JOGO!"), 0, 0);
            mostrarPontuacao();
        }
    }
}

void Jogo::apresentarPergunta() {
    if (_perguntaAtualIndex < _numPerguntasCarregadas) {
        char pergunta[80]; // Buffer temporário
        _perguntas[_perguntaAtualIndex]->getTexto(pergunta, 80);
        _display.escreverScroll(pergunta, 0, 600); // Mostra a pergunta na linha 0 (velocidade mais lenta)
        _display.escrever(F("Aperte o botao!"), 0, 1); // Mensagem na linha 1
    }
}

void Jogo::aguardarRespostaJogador() {
    for (int i = 0; i < _numJogadores; i++) {
        if (_botoesResposta[i]->lerEstado()) {
            // Jogador respondeu!
            _jogadorQueRespondeu = i;
            _lampadas[i]->acender();
            mudarEstado(AGUARDANDO_PONTUACAO_MEDIADOR);
            return;
        }
    }
}

void Jogo::aguardarPontuacaoMediador() {
    // Exibe quem respondeu
    _display.escrever(_jogadores[_jogadorQueRespondeu]->getNome(), 0, 0);
    _display.escrever(F("respondeu!"), 0, 1);

    // Aguarda um pequeno delay após entrar neste estado para evitar detecção falsa
    // de botões logo após a mudança de estado (problema de ruído/inicialização)
    if (millis() - _tempoDaUltimaAcao < 100) {
        return; // Ignora leituras nos primeiros 100ms após mudar para este estado
    }

    // Verifica botões de pontuação do mediador
    for (int i = 0; i < _numJogadores; i++) {
        if (_botoesPonto[i] != nullptr && _botoesPonto[i]->lerEstado()) {
            // Ponto para o jogador i
            _jogadores[i]->adicionarPontos(1);
            Serial.print(_jogadores[i]->getNome());
            Serial.println(F(" pontuou!"));
            
            // Apaga a luz do jogador que respondeu
            _lampadas[_jogadorQueRespondeu]->apagar();
            
            // Avança para a próxima rodada
            _perguntaAtualIndex++;
            mudarEstado(MOSTRANDO_PONTUACAO);
            return;
        }
    }
}

void Jogo::mostrarPontuacao() {
    _display.escrever(F("Pontuacao:"), 0, 0);
    char pontuacaoStr[17];
    char nome1 = _jogadores[0]->getNome()[0];
    char nome2 = _jogadores[1]->getNome()[0];
    snprintf_P(pontuacaoStr, 17, PSTR("%c:%d  %c:%d"), 
               nome1, _jogadores[0]->getPontuacao(),
               nome2, _jogadores[1]->getPontuacao());
    _display.escrever(pontuacaoStr, 0, 1);

    // Espera o tempo definido antes de ir para a próxima pergunta
    if (millis() - _tempoDaUltimaAcao >= TEMPO_MOSTRAR_PONTUACAO) {
        mudarEstado(APRESENTANDO_PERGUNTA);
    }
}

void Jogo::reiniciarJogo() {
    iniciarJogo();
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

