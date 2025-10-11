#ifndef Pergunta_h
#define Pergunta_h

#include <Arduino.h>

class Pergunta {
public:
    Pergunta(String texto, String respostaCorreta);
    String getTexto();
    String getRespostaCorreta();

private:
    String _texto;
    String _respostaCorreta;
};

#endif

