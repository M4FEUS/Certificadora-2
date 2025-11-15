#include "DisplayLCD.h"

DisplayLCD::DisplayLCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : _lcd(lcd_Addr, lcd_cols, lcd_rows) {
    _cols = lcd_cols;
    _rows = lcd_rows;
}

void DisplayLCD::iniciar() {
    _lcd.init();
    _lcd.backlight();
}

void DisplayLCD::limpar() {
    _lcd.clear();
}

void DisplayLCD::escrever(String texto, int coluna, int linha) {
    _lcd.setCursor(coluna, linha);
    _lcd.print(texto);
}

void DisplayLCD::escreverScroll(String texto, int linha, int delayScroll) {
    limpar();
    if (texto.length() > _cols) {
        for (int i = 0; i <= texto.length() - _cols; i++) {
            _lcd.setCursor(0, linha);
            _lcd.print(texto.substring(i, i + _cols));
            delay(delayScroll);
        }
    } else {
        escrever(texto, 0, linha);
    }
}
