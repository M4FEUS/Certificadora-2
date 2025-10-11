#include "Pergunta.h"

Pergunta::Pergunta(String texto, String respostaCorreta) {
    _texto = texto;
    _respostaCorreta = respostaCorreta;
}

String Pergunta::getTexto() {
    return _texto;
}

String Pergunta::getRespostaCorreta() {
    return _respostaCorreta;
}

