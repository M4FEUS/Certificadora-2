#ifndef Lampada_h
#define Lampada_h

#include <Arduino.h>

class Lampada {
public:
    Lampada(int pino);
    void acender();
    void apagar();
    bool estaAcesa();

private:
    int _pino;
    bool _estado;
};

#endif

