#ifndef DisplayLCD_h
#define DisplayLCD_h

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class DisplayLCD {
public:
    DisplayLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
    void iniciar();
    void limpar();
    void escrever(String texto, int coluna, int linha);
    void escreverScroll(String texto, int linha, int delayScroll);

private:
    LiquidCrystal_I2C _lcd;
    uint8_t _cols;
    uint8_t _rows;
};

#endif
