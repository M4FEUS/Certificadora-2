// ==========================================================================
// Sketch Principal: CienciaOuConsequencia.ino
// ==========================================================================
// Este arquivo é o ponto de entrada do projeto. Ele é responsável por:
// 1. Incluir todas as classes do projeto.
// 2. Definir os pinos do hardware (botões, lâmpadas, potenciômetro).
// 3. Criar as listas de perguntas, separadas por nível de dificuldade.
// 4. Instanciar os objetos (Jogo, Jogadores, Botões, Lâmpadas).
// 5. Configurar o jogo no setup(), lendo o nível de dificuldade
//    do potenciômetro e carregando as perguntas correspondentes.
// 6. Executar o loop principal do jogo na função loop().
// ==========================================================================

#include "Jogo.h"
#include "Jogador.h"
#include "Botao.h"
#include "Lampada.h"
#include "Pergunta.h"

// --- Configuração dos Pinos do Hardware ---
// Jogador 1
const int PINO_BOTAO_J1 = 2;
const int PINO_LAMPADA_J1 = 3;

// Jogador 2
const int PINO_BOTAO_J2 = 4;
const int PINO_LAMPADA_J2 = 5;

// Potenciômetro para seleção de dificuldade
const int PINO_POTENCIOMETRO = A0;

// --- Instanciação dos Objetos Globais ---
Jogo meuJogo;

Jogador jogador1("Jogador 1");
Botao botaoJ1(PINO_BOTAO_J1);
Lampada lampadaJ1(PINO_LAMPADA_J1);

Jogador jogador2("Jogador 2");
Botao botaoJ2(PINO_BOTAO_J2);
Lampada lampadaJ2(PINO_LAMPADA_J2);


// ==========================================================================
// BANCO DE PERGUNTAS
// ==========================================================================

// --- NÍVEL FÁCIL (Crianças) ---
Pergunta perguntasFaceis[] = {
    Pergunta("Qual peixe e o Bolhas da animacao Procurando Nemo?\n(a) peixe-palhaco\n(b) cirurgiao-amarelo\n(c) peixe donzela\n(d) dourado", "b"),
    Pergunta("Qual e a coloracao da ave papa-leguas?\n(a) amarela e preta\n(b) azul\n(c) marrom\n(d) amarela", "c"),
    Pergunta("O personagem Manny da franquia A era do Gelo, na vida real e qual animal?\n(a) Preguica-gigante\n(b) Mamute-lanoso\n(c) Tigre-dente-de-sabre\n(d) Dinossauro", "b"),
    Pergunta("Complete: A Terra, planeta em que vivemos, tem formato...\n(a) Plano\n(b) Esferico\n(c) De rosquinha americana\n(d) De um prato de cozinha", "b"),
    Pergunta("A personagem Dory da franquia Procurando o Nemo, na vida real, e qual animal?\n(a) Peixe palhaco\n(b) Cirurgiao-pateta\n(c) Cirurgiao-patela\n(d) Peixe-leao", "b"), // O peixe é um Cirurgião-patela
    Pergunta("O personagem Lula molusco do desenho Bob Esponja, na vida real e qual animal?\n(a) Lula\n(b) Polvo\n(c) Siri\n(d) Esponja-do-mar", "b"),
    Pergunta("Quais sao as fases da Lua?\n(a) Minguante, crescente, nova e cheia\n(b) Nova, cheia, superlua e eclipse\n(c) Penumbral, lunar parcial, lunar total e cheia\n(d) Lua de sangue, eclipse, minguante e nova", "a"),
    Pergunta("Qual o nome popular do cloreto de sodio?\n(a) Alcool\n(b) Sal de Cozinha\n(c) Fermento Biologico\n(d) Vinagre", "b"),
    Pergunta("Quantas estrelas fazem parte do Cruzeiro do Sul?\n(a) 4 estrelas\n(b) 3 estrelas\n(c) 5 estrelas\n(d) 6 estrelas", "c"),
    Pergunta("Quantos minutos tem em tres horas?\n(a) 60 minutos\n(b) 90 minutos\n(c) 120 minutos\n(d) 180 minutos", "d"),
    Pergunta("Quantos coracoes tem um polvo?\n(a) 1 coracao\n(b) 2 coracoes\n(c) 3 coracoes\n(d) 4 coracoes", "c"),
    Pergunta("Qual ave e capaz de bater as asas ate 200 vezes por segundo?\n(a) falcao\n(b) bem-te-vi\n(c) quero-quero\n(d) beija-flor", "d")
};

// --- NÍVEL MÉDIO (Fundamental 2 e Ensino Médio) ---
Pergunta perguntasMedias[] = {
    Pergunta("No Sistema Solar onde habitamos, qual destes e o planeta mais quente?\n(a) Sol\n(b) Venus\n(c) Mercurio\n(d) Saturno", "b"),
    Pergunta("O microondas faz mal a saude devido a radiacao?\n(a) Sim\n(b) So se voce ficar na frente quando ele estiver funcionando\n(c) Nao\n(d) Apenas modelos antigos", "c"),
    Pergunta("A frase 'Se nao existe vida fora da Terra, entao, o universo e um grande desperdicio de espaco' pertence a qual cientista?\n(a) Robert Pattinson\n(b) Carl Sagan\n(c) Albert Einstein\n(d) Castro Alves", "b"),
    Pergunta("Atualmente, quantos elementos quimicos tem na tabela periodica?\n(a) 118\n(b) 92\n(c) 100\n(d) 210", "a"),
    Pergunta("Qual o acido que esta presente nas baterias dos carros?\n(a) cloridrico\n(b) sulfurico\n(c) fluoridrico\n(d) carbonico", "b"),
    Pergunta("Qual o gas que e adicionado aos refrigerantes?\n(a) oxigenio\n(b) fluor\n(c) metano\n(d) carbonico", "d"),
    Pergunta("Quais sao, respectivamente, o menor e o maior pais do mundo?\n(a) Sao Marino e India\n(b) Monaco e Canada\n(c) Vaticano e Russia\n(d) Nauru e China", "c"),
    Pergunta("Na mitologia romana, qual animal amamentou os gemeos Romulo e Remo?\n(a) Uma vaca\n(b) Uma cabra\n(c) Uma ovelha\n(d) Uma loba", "d"),
    Pergunta("A ilha de Madagascar e banhada por qual Oceano?\n(a) Pacifico\n(b) Artico\n(c) Indico\n(d) Atlantico", "c"),
    Pergunta("Quais dos orgaos abaixo pertencem ao sistema respiratorio?\n(a) Laringe e Traqueia\n(b) Esofago e Bronquios\n(c) Alveolos e Pancreas\n(d) Pulmoes e Faringe", "d"),
    Pergunta("Ao atingir a fase adulta, quantos ossos os seres humanos possuem no corpo?\n(a) 300\n(b) 297\n(c) 276\n(d) 206", "d"),
    Pergunta("Qual o monumento famoso pela sua inclinacao?\n(a) Torre de Pisa\n(b) Pantheon\n(c) Torre Eiffel\n(d) Estatua da Liberdade", "a"),
    Pergunta("Ano-luz e uma medida de qual grandeza?\n(a) Tempo\n(b) Comprimento\n(c) Idade\n(d) Quantidade de materia", "b"),
    Pergunta("Por que o ar condicionado e colocado na parte superior da sala?\n(a) Para evitar que as pessoas batam a cabeca\n(b) Porque e a posicao que normalmente ficam as tomadas\n(c) Porque e mais facil para apontar o controle remoto\n(d) Porque o ar frio e mais denso do que o ar quente", "d"),
    Pergunta("Por que vemos a lua brilhando a noite?\n(a) Porque ela e uma estrela e tem luz propria\n(b) Porque ela e composta de elementos fluorescentes\n(c) Porque ela esta muito quente\n(d) Porque ele reflete a luz do sol", "d"),
    Pergunta("Quantos seculos ha em um milenio?\n(a) 10 seculos\n(b) 100 seculos\n(c) 50 seculos\n(d) 5 seculos", "a"),
    Pergunta("De que e obtida a energia eolica?\n(a) Agua\n(b) Sol\n(c) Vento\n(d) Mares", "c"),
    Pergunta("Quantos dentes tem uma pessoa adulta, se nao perdeu nenhum?\n(a) 22\n(b) 32\n(c) 42\n(d) 28", "b"),
    Pergunta("Qual e o pais com maior extensao territorial?\n(a) Brasil\n(b) Canada\n(c) China\n(d) Russia", "d"),
    Pergunta("Em qual pais foi detectado o primeiro caso de COVID-19?\n(a) India\n(b) Russia\n(c) China\n(d) Japao", "c"),
    Pergunta("Qual desses paises nao faz fronteira com o Brasil?\n(a) Venezuela\n(b) Paraguai\n(c) Argentina\n(d) Equador", "d")
};

// --- NÍVEL DIFÍCIL (Universitários e Adultos) ---
Pergunta perguntasDificeis[] = {
    Pergunta("Na natureza nao existe macho alfa. Essa afirmacao esta?\n(a) Correta\n(b) Nao ha consenso\n(c) Errada\n(d) Depende da especie", "a"),
    Pergunta("Qual destes animais tem maior concentracao de proteina?\n(a) Bois\n(b) Gafanhoto\n(c) Percevejo\n(d) Frango", "b"), // Gafanhotos são uma fonte rica em proteína
    Pergunta("Quais os beneficios do Sal quantico?\n(a) Noites de sonos alucinogenas\n(b) Alinhamento de chackras\n(c) O sal quantico e um mito feito pela industria para se aproveitar do desconhecimento das pessoas\n(d) Nenhum dos anteriores", "c"),
    Pergunta("A frase 'Estou entre aqueles que acham que a ciencia tem uma grande beleza' pertence a qual cientista?\n(a) Marie Curie\n(b) Amy Winehouse\n(c) Xuxa meneghel\n(d) Fatima Bernardes", "a"),
    Pergunta("Qual o elemento quimico que consegue formar cadeias e que existe com abundancia nos compostos organicos?\n(a) Oxigenio\n(b) Magnesio\n(c) Carbono\n(d) Cloro", "c"),
    Pergunta("Qual o elemento quimico mais abundante no universo?\n(a) Carbono\n(b) Oxigenio\n(c) Helio\n(d) Hidrogenio", "d"),
    Pergunta("Qual da Lei da Fisica Classica, enunciada por Isaac Newton, e responsavel por explicar que o 'pum' nos empurra?\n(a) 3a ('acao e reacao')\n(b) 1a (Inercia)\n(c) 2a (Principio Fundamental da Dinamica)\n(d) zero (Equilibrio termico)", "a"),
    Pergunta("O que a palavra 'legend' significa em portugues?\n(a) Legenda\n(b) Lenda\n(c) Historia\n(d) Legendario", "b"),
    Pergunta("Qual das alternativas a seguir contem apenas classes de palavras?\n(a) Artigo, verbo transitivo e verbo intransitivo\n(b) Substantivo, adjetivo e preposicao\n(c) Fonologia, morfologia e sintaxe\n(d) Onomatopeia, semantica e verbo", "b"),
    Pergunta("Qual o nome do cientista que descobriu o processo de pasteurizacao (esterilizacao de alimentos) e a vacina contra a raiva?\n(a) Louis Pasteur\n(b) Blaise Pascal\n(c) Antoine Lavoisier\n(d) Gregor Mendel", "a"),
    Pergunta("A corrente eletrica que permite voce carregar seu celular, entre outras coisas e composta de\n(a) Eletrons em movimento\n(b) Atomos em movimento\n(c) Luz em movimento\n(d) Energia em movimento", "a"),
    Pergunta("Por que uma garrafa de vidro cheia de liquido explode se voce esquece-la no congelador?\n(a) Porque a tampa e de metal\n(b) Porque o vidro sofre uma expansao quando e resfriado\n(c) Porque o liquido sofre uma expansao quando e resfriado\n(d) Porque o congelador aplica um gradiente termico na garrafa", "c"),
    Pergunta("Quantos anos ha em dois seculos e meio?\n(a) 250 anos\n(b) 150 anos\n(c) 225 anos\n(d) 200 anos", "a"),
    Pergunta("Quais sao os idiomas oficiais do Canada?\n(a) Ingles e espanhol\n(b) Ingles e frances\n(c) Ingles e russo\n(d) Ingles e portugues", "b"),
    Pergunta("Quanto tempo durou a guerra dos 100 anos?\n(a) 116 anos\n(b) 100 anos\n(c) 99 anos\n(d) 110 anos", "a"),
    Pergunta("Quais cidades japonesas foram atingidas pelas bombas atomicas lancadas pelos Estados Unidos em 1945?\n(a) Hiroshima e Osaka\n(b) Hiroshima e Nagasaki\n(c) Toquio e Osaka\n(d) Toquio e Yokohama", "b"),
    Pergunta("Quantos centimetros tem 1 metro e meio?\n(a) 100 centimetros\n(b) 150 centimetros\n(c) 160 centimetros\n(d) 120 centimetros", "b")
};

void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ; // Espera a porta serial conectar. Necessário para placas como Leonardo.
    }
    
    // Inicializa o gerador de números aleatórios para embaralhar as perguntas
    // Use um pino analógico não conectado para uma semente mais aleatória
    randomSeed(analogRead(A1));

    Serial.println("Bem-vindo ao Ciencia ou Consequencia!");
    Serial.println("Configurando o jogo...");

    // Adiciona os jogadores, botões e lâmpadas ao jogo
    // A ordem de adição é importante
    meuJogo.adicionarJogador(jogador1);
    meuJogo.adicionarBotao(botaoJ1);
    meuJogo.adicionarLampada(lampadaJ1);

    meuJogo.adicionarJogador(jogador2);
    meuJogo.adicionarBotao(botaoJ2);
    meuJogo.adicionarLampada(lampadaJ2);

    // --- Seleção de Dificuldade via Potenciômetro ---
    int valorPot = analogRead(PINO_POTENCIOMETRO);
    
    // O valor do potenciômetro varia de 0 a 1023. Dividimos em 3 faixas.
    if (valorPot < 341) { // 0-340: Nível Fácil
        Serial.println("Nivel de dificuldade selecionado: FACIL");
        int numPerguntas = sizeof(perguntasFaceis) / sizeof(Pergunta);
        meuJogo.carregarPerguntas(perguntasFaceis, numPerguntas);

    } else if (valorPot < 682) { // 341-681: Nível Médio
        Serial.println("Nivel de dificuldade selecionado: MEDIO");
        int numPerguntas = sizeof(perguntasMedias) / sizeof(Pergunta);
        meuJogo.carregarPerguntas(perguntasMedias, numPerguntas);

    } else { // 682-1023: Nível Difícil
        Serial.println("Nivel de dificuldade selecionado: DIFICIL");
        int numPerguntas = sizeof(perguntasDificeis) / sizeof(Pergunta);
        meuJogo.carregarPerguntas(perguntasDificeis, numPerguntas);
    }
    
    // Inicia o jogo
    meuJogo.iniciarJogo();
}

void loop() {
    // A classe Jogo gerencia toda a lógica da rodada.
    // O loop principal só precisa chamar este método.
    meuJogo.executarRodada();
}