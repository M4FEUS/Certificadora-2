#ifndef Pergunta_h
#define Pergunta_h

#include <Arduino.h>
#include <avr/pgmspace.h>

class Pergunta {
public:
    Pergunta(); // Construtor padrão
    Pergunta(const char* textoPROGMEM, char respostaCorreta);
    void getTexto(char* buffer, int tamanho);
    char getRespostaCorreta();

private:
    const char* _textoPROGMEM; // Ponteiro para string em PROGMEM
    char _respostaCorreta; // Removido const para permitir atribuição
};

#endif

