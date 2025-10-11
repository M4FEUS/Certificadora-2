# Projeto: Ciência ou Consequência

## Visão Geral

O projeto "Ciência ou Consequência" é um jogo interativo desenvolvido para a divulgação e popularização da ciência, utilizando uma plataforma Arduino. Inspirado em game shows, ele combina competição com conhecimentos gerais para estimular o aprendizado e o engajamento do público. Este repositório contém o código-fonte e a documentação para uma versão aprimorada do jogo, com foco na aplicação de conceitos de Programação Orientada a Objetos (POO) e Estruturas de Dados para uma arquitetura mais modular e escalável.

## Funcionalidades

### Funcionalidades Atuais (Base do Projeto Existente)

*   **Sistema Interativo:** Utiliza botões de pressão e lâmpadas controladas por um microcontrolador Arduino.
*   **Dinâmica de Jogo:** Permite a participação de múltiplos jogadores, com um mediador para perguntas e detecção do primeiro a responder.
*   **Perguntas Personalizáveis:** Capacidade de adaptar o conteúdo das perguntas para diferentes públicos e eventos.
*   **Portabilidade:** Design que facilita o transporte e aplicação em diversos contextos de extensão.

### Melhorias Implementadas (Foco da Reestruturação)

*   **Código Orientado a Objetos (POO):** Reestruturação do software utilizando classes para representar os elementos do jogo (`Botao`, `Lampada`, `Jogador`, `Pergunta`, `Jogo`).
*   **Gerenciamento de Perguntas com Estruturas de Dados:** Utilização de arrays de objetos `Pergunta` para armazenar e gerenciar o banco de perguntas de forma flexível, com potencial para carregamento dinâmico (ex: via SD Card).
*   **Algoritmos Aprimorados:** Implementação de algoritmos para embaralhamento de perguntas (Fisher-Yates) e detecção otimizada do primeiro botão pressionado.
*   **Modularidade e Escalabilidade:** A arquitetura POO facilita a adição de novas funcionalidades, componentes e a manutenção do código.

## Estrutura do Projeto

O projeto é organizado em arquivos `.h` (cabeçalhos) e `.cpp` (implementação) para cada classe, além do arquivo principal `.ino` do Arduino:

*   `Botao.h`, `Botao.cpp`: Gerencia a leitura e o estado de um botão físico.
*   `Lampada.h`, `Lampada.cpp`: Controla o acionamento e o estado de uma lâmpada.
*   `Jogador.h`, `Jogador.cpp`: Representa um jogador, com nome e pontuação.
*   `Pergunta.h`, `Pergunta.cpp`: Armazena o texto e a resposta correta de uma pergunta.
*   `Jogo.h`, `Jogo.cpp`: Orquestra a lógica principal do jogo, gerenciando jogadores, botões, lâmpadas e perguntas.
*   `CienciaOuConsequencia.ino`: O sketch principal do Arduino, onde as classes são instanciadas e a lógica do jogo é executada no `setup()` e `loop()`.

## Como Usar (Instalação e Configuração)

1.  **Instale o Arduino IDE:** Baixe e instale a versão mais recente do [Arduino IDE](https://www.arduino.cc/en/software).
2.  **Clone o Repositório:**
    ```bash
    git clone https://github.com/M4FEUS/Certificadora-2.git
    cd Certificadora-2
    ```
3.  **Organize os Arquivos:** Certifique-se de que os arquivos `.h` e `.cpp` de cada classe estejam na mesma pasta do arquivo `.ino` ou em subpastas reconhecidas pelo Arduino IDE (geralmente, o Arduino IDE trata arquivos `.h` e `.cpp` na mesma pasta do `.ino` como parte do sketch).
4.  **Conecte o Hardware:** Monte o circuito do jogo "Ciência ou Consequência" conectando os botões, lâmpadas (via relé) e o Arduino conforme o esquema elétrico (a ser fornecido na documentação técnica).
5.  **Carregue o Código:**
    *   Abra o arquivo `CienciaOuConsequencia.ino` no Arduino IDE.
    *   Selecione a placa Arduino correta (ex: Arduino Uno) em `Ferramentas > Placa`.
    *   Selecione a porta serial correta em `Ferramentas > Porta`.
    *   Clique em `Upload` para carregar o código para o seu Arduino.
6.  **Interaja:** Abra o Monitor Serial (Ctrl+Shift+M) para ver as perguntas e o status do jogo.

## Licença

Este projeto está licenciado sob a [Licença MIT](https://opensource.org/licenses/MIT). Veja o arquivo `LICENSE` para mais detalhes.
