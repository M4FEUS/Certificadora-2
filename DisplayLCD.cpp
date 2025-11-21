#include "DisplayLCD.h"
#include <avr/pgmspace.h>
#include <string.h>

// Construtor: Recebe os pinos e configura a biblioteca LiquidCrystal
DisplayLCD::DisplayLCD(uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) 
    : _lcd(rs, en, d4, d5, d6, d7) {
    // Definimos o tamanho padrão aqui (pode ser ajustado se necessário)
    _cols = 16;
    _rows = 2;
}

void DisplayLCD::iniciar() {
    _lcd.begin(_cols, _rows); // Inicia o LCD com 16 colunas e 2 linhas
    // _lcd.backlight(); // A biblioteca padrão não controla backlight por software na maioria das ligações diretas
}

void DisplayLCD::limpar() {
    _lcd.clear();
}

void DisplayLCD::escrever(const char* texto, int coluna, int linha) {
    _lcd.setCursor(coluna, linha);
    // Para strings na RAM, usa diretamente
    _lcd.print(texto);
}

void DisplayLCD::escrever(const __FlashStringHelper* texto, int coluna, int linha) {
    _lcd.setCursor(coluna, linha);
    // Para strings PROGMEM (F()), usa print com FlashStringHelper
    _lcd.print(texto);
}

void DisplayLCD::escreverScroll(const char* texto, int linha, int delayScroll) {
    limpar();
    int len = strlen(texto);
    if (len > _cols) {
        for (int i = 0; i <= len - _cols; i++) {
            _lcd.setCursor(0, linha);
            char buffer[17];
            strncpy(buffer, texto + i, _cols);
            buffer[_cols] = '\0';
            _lcd.print(buffer);
            delay(delayScroll);
        }
    } else {
        escrever(texto, 0, linha);
    }
}

void DisplayLCD::escreverScroll(const __FlashStringHelper* texto, int linha, int delayScroll) {
    limpar();
    // Para FlashStringHelper, precisamos calcular o tamanho primeiro
    const char* p = (const char*)texto;
    int len = 0;
    while (pgm_read_byte(p + len) != '\0') len++;
    
    if (len > _cols) {
        for (int i = 0; i <= len - _cols; i++) {
            _lcd.setCursor(0, linha);
            char buffer[17];
            for (int j = 0; j < _cols && (i + j) < len; j++) {
                buffer[j] = pgm_read_byte(p + i + j);
            }
            buffer[_cols] = '\0';
            _lcd.print(buffer);
            delay(delayScroll);
        }
    } else {
        escrever(texto, 0, linha);
    }
}