#ifndef DisplayLCD_h
#define DisplayLCD_h

#include <Arduino.h>
#include <LiquidCrystal.h> // Mudamos para a biblioteca padrão

class DisplayLCD {
public:
    // O construtor agora pede os pinos, não o endereço
    DisplayLCD(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    
    void iniciar();
    void limpar();
    void escrever(const char* texto, int coluna, int linha);
    void escrever(const __FlashStringHelper* texto, int coluna, int linha); // Sobrecarga para F()
    void escreverScroll(const char* texto, int linha, int delayScroll);
    void escreverScroll(const __FlashStringHelper* texto, int linha, int delayScroll); // Sobrecarga para F()

private:
    LiquidCrystal _lcd; // Objeto da biblioteca padrão
    uint8_t _cols;
    uint8_t _rows;
};

#endif