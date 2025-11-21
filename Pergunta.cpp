#include "Pergunta.h"

Pergunta::Pergunta() : _textoPROGMEM(nullptr), _respostaCorreta('\0') {
}

Pergunta::Pergunta(const char* textoPROGMEM, char respostaCorreta) 
    : _textoPROGMEM(textoPROGMEM), _respostaCorreta(respostaCorreta) {
}

void Pergunta::getTexto(char* buffer, int tamanho) {
    if (_textoPROGMEM == nullptr) {
        buffer[0] = '\0';
        return;
    }
    strncpy_P(buffer, _textoPROGMEM, tamanho - 1);
    buffer[tamanho - 1] = '\0';
}

char Pergunta::getRespostaCorreta() {
    return _respostaCorreta;
}

