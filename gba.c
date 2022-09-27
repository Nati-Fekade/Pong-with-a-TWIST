#include "gba.h"

// The start of the video memory
unsigned volatile short *videoBuffer = (unsigned short*)0x6000000;

// Miscellaneous Functions
int collision(int colA, int rowA, int widthA, int heightA, int colB, int rowB, int widthB, int heightB) {
    return rowA <= rowB + heightB - 1 && rowA + heightA - 1 >= rowB && colA <= colB + widthB - 1 && colA + widthA - 1 >= colB;
}

void waitForVBlank() {
    while (SCANLINECOUNTER >= 160);
    while (SCANLINECOUNTER < 160);
}

// Mode 3 Drawing Functions

void setPixel(int col, int row, unsigned short color) {
    videoBuffer[OFFSET(col, row, SCREENWIDTH)] = color;
}

void drawRectangle(int col, int row, int width, int height, volatile unsigned short color) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            setPixel((col + i), (row + j), color);
        }
    }
}

void fillScreen(volatile unsigned short color) {
    for (int i = 0; i < 38400; i++) {
        videoBuffer[i] = color;
    }
}

void drawHorizontal(int col, int row, int size, volatile unsigned short color) {
    for (int i = 0; i < size; i++) {
        setPixel(col + i, row, color);
    }
}