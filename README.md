# Projeto: Ciência ou Consequência

## Visão Geral

O projeto "Ciência ou Consequência" é um jogo interativo desenvolvido para a divulgação e popularização da ciência, utilizando uma plataforma Arduino. Inspirado em game shows, ele combina competição com conhecimentos gerais para estimular o aprendizado e o engajamento do público. Este repositório contém o código-fonte e a documentação para uma versão aprimorada do jogo, com foco na aplicação de conceitos de Programação Orientada a Objetos (POO) e Estruturas de Dados para uma arquitetura mais modular e escalável.

## Funcionalidades

### Funcionalidades Principais

*   **Sistema Interativo:** Utiliza botões de pressão e lâmpadas controladas por um microcontrolador Arduino.
*   **Display LCD:** Interface visual com display LCD 16x2 para exibir perguntas e pontuações.
*   **Sistema de Dificuldade:** Potenciômetro para seleção de 3 níveis de dificuldade (Fácil, Médio, Difícil).
*   **Dinâmica de Jogo:** Permite a participação de 2 jogadores, com um mediador para pontuação e detecção do primeiro a responder.
*   **Perguntas Personalizáveis:** Banco de perguntas organizado por nível de dificuldade, armazenado na memória flash (PROGMEM).
*   **Embaralhamento de Perguntas:** Algoritmo Fisher-Yates para embaralhar as perguntas a cada partida.
*   **Portabilidade:** Design que facilita o transporte e aplicação em diversos contextos de extensão.

### Arquitetura e Melhorias

*   **Código Orientado a Objetos (POO):** Reestruturação do software utilizando classes para representar os elementos do jogo (`Botao`, `Lampada`, `Jogador`, `Pergunta`, `Jogo`, `DisplayLCD`).
*   **Gerenciamento de Perguntas com Estruturas de Dados:** Utilização de arrays de objetos `Pergunta` para armazenar e gerenciar o banco de perguntas de forma flexível.
*   **Otimização de Memória:** Uso de PROGMEM para armazenar perguntas na memória flash, economizando RAM.
*   **Algoritmos Aprimorados:** Implementação de algoritmos para embaralhamento de perguntas (Fisher-Yates) e detecção otimizada do primeiro botão pressionado.
*   **Modularidade e Escalabilidade:** A arquitetura POO facilita a adição de novas funcionalidades, componentes e a manutenção do código.

## Estrutura do Projeto

O projeto é organizado em arquivos `.h` (cabeçalhos) e `.cpp` (implementação) para cada classe, além do arquivo principal `.ino` do Arduino:

*   `Botao.h`, `Botao.cpp`: Gerencia a leitura e o estado de um botão físico, com proteção contra detecções falsas.
*   `Lampada.h`, `Lampada.cpp`: Controla o acionamento e o estado de uma lâmpada.
*   `Jogador.h`, `Jogador.cpp`: Representa um jogador, com nome e pontuação.
*   `Pergunta.h`, `Pergunta.cpp`: Armazena o texto e a resposta correta de uma pergunta.
*   `DisplayLCD.h`, `DisplayLCD.cpp`: Gerencia a exibição no display LCD, incluindo scroll de texto.
*   `Jogo.h`, `Jogo.cpp`: Orquestra a lógica principal do jogo, gerenciando jogadores, botões, lâmpadas, perguntas e estados do jogo.
*   `Certificadora-2.ino`: O sketch principal do Arduino, onde as classes são instanciadas e a lógica do jogo é executada no `setup()` e `loop()`.

## Hardware Necessário

### Componentes

*   Arduino Uno (ou compatível)
*   Display LCD 16x2
*   2 Botões para os jogadores
*   2 Botões para o mediador (pontuação)
*   2 LEDs/Lâmpadas (ou módulos de LED)
*   1 Potenciômetro 10k (B10k)
*   Resistores conforme necessário

### Conexões dos Pinos

#### Display LCD (Modo 4 bits)
*   RS → Pino 7
*   E → Pino 6
*   D4 → Pino 5
*   D5 → Pino 4
*   D6 → Pino 3
*   D7 → Pino 2

#### Jogador 1
*   Botão de Resposta → Pino 10
*   Lâmpada/LED → Pino 12

#### Jogador 2
*   Botão de Resposta → Pino 11
*   Lâmpada/LED → Pino 9

#### Mediador
*   Botão Pontuar Jogador 1 → Pino A5
*   Botão Pontuar Jogador 2 → Pino A4

#### Potenciômetro
*   Pino Central (Wiper) → Pino A0
*   Um pino externo → GND
*   Outro pino externo → VCC (5V)

## Como Usar (Instalação e Configuração)

1.  **Instale o Arduino IDE:** Baixe e instale a versão mais recente do [Arduino IDE](https://www.arduino.cc/en/software).

2.  **Clone o Repositório:**
    ```bash
    git clone https://github.com/M4FEUS/Certificadora-2.git
    cd Certificadora-2
    ```

3.  **Organize os Arquivos:** Certifique-se de que os arquivos `.h` e `.cpp` de cada classe estejam na mesma pasta do arquivo `.ino` ou em subpastas reconhecidas pelo Arduino IDE (geralmente, o Arduino IDE trata arquivos `.h` e `.cpp` na mesma pasta do `.ino` como parte do sketch).

4.  **Conecte o Hardware:** Monte o circuito do jogo "Ciência ou Consequência" conectando os componentes conforme as especificações acima.

5.  **Carregue o Código:**
    *   Abra o arquivo `Certificadora-2.ino` no Arduino IDE.
    *   Selecione a placa Arduino correta (ex: Arduino Uno) em `Ferramentas > Placa`.
    *   Selecione a porta serial correta em `Ferramentas > Porta`.
    *   Clique em `Upload` para carregar o código para o seu Arduino.

6.  **Inicie o Jogo:**
    *   Após o upload, o jogo iniciará automaticamente.
    *   O display mostrará "Selecione Nivel" - você tem 3 segundos para ajustar o potenciômetro:
        - **Fácil:** Gire para a esquerda (valores 0-340)
        - **Médio:** Gire para o meio (valores 341-681)
        - **Difícil:** Gire para a direita (valores 682-1023)
    *   O nível selecionado será exibido no display.

7.  **Jogar:**
    *   As perguntas aparecerão no display LCD.
    *   O primeiro jogador a apertar seu botão acende sua lâmpada.
    *   O mediador avalia a resposta e pressiona o botão correspondente para pontuar.
    *   A pontuação é exibida após cada rodada.
    *   O jogo termina quando todas as perguntas forem respondidas.

8.  **Monitor Serial (Opcional):** Abra o Monitor Serial (Ctrl+Shift+M, 9600 baud) para ver informações de debug e status do jogo.

## Níveis de Dificuldade

O jogo possui 3 níveis de dificuldade, cada um com seu próprio banco de perguntas:

*   **Fácil:** 12 perguntas
*   **Médio:** 21 perguntas
*   **Difícil:** 17 perguntas

As perguntas são embaralhadas aleatoriamente a cada partida usando o algoritmo Fisher-Yates.

## Licença

Este projeto está licenciado sob a [Licença MIT](https://opensource.org/licenses/MIT). Veja o arquivo `LICENSE` para mais detalhes.
