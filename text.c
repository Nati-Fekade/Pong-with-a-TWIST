#include "gba.h"
#include "text.h"
#include "font.h"

// Draws the specified character at the specified location in Mode 3
void drawChar(int col, int row, char ch, unsigned short color) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            if (fontdata_6x8[48*ch + i + 6*j]) {
                setPixel(col + i, row + j, color);
            }
        }
    }
} 

// Draws the specified string at the specified location in Mode 3
void drawString(int col, int row, char *str, unsigned short color) {
    while (*str) {
        drawChar(col, row, *str++, color);
        col += 6;
    }
}