#ifndef GBA_H
#define GBA_H

// Common typedefs
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

// Common Macro
#define OFFSET(col, row, rowLength) ((row) * (rowLength) + (col))

// Miscellaneous Functions
int collision(int colA, int rowA, int widthA, int heightA, int colB, int rowB, int widthB, int heightB);
void waitForVBlank();

// -- Display--
// Display Control Register Macros
#define REG_DISPCTL (*(volatile unsigned short *)0x4000000)
#define MODE3 3
#define BG2_ENABLE (1<<10)

// Display Status Registers
#define SCANLINECOUNTER (*(volatile unsigned short *)0x4000006)

// Display Constants
#define SCREENHEIGHT 160
#define SCREENWIDTH 240

// Video Buffer
extern volatile unsigned short *videoBuffer;

// ---- Color ----

// Colors
#define COLOR(r,g,b) ((r) | (g)<<5 | (b)<<10)
#define BLACK 0
#define GRAY COLOR(15,15,15)
#define WHITE COLOR(31,31,31)
#define RED COLOR(31,0,0)
#define GREEN COLOR(0,31,0)
#define BLUE COLOR(0,0,31)
#define CYAN COLOR(0,31,31)
#define MAGENTA COLOR(31,0,31)
#define YELLOW COLOR(31,31,0)

// Mode 3

// Mode 3 Drawing Functions
void setPixel(int col, int row, unsigned short color);
void drawRectangle(int col, int row, int width, int height, volatile unsigned short color);
void fillScreen(volatile unsigned short color);
void drawHorizontal(int col, int row, int size, volatile unsigned short color);

// Input

// Button Register
#define BUTTONS (*(volatile unsigned short *)0x04000130)

// Button Masks
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

// Variables for Button Macros
extern unsigned short oldButtons;
extern unsigned short buttons;

// Button Macros
#define BUTTON_HELD(key)    (~(BUTTONS) & (key))
#define BUTTON_PRESSED(key) (!(~(oldButtons) & (key)) && (~buttons & (key)))

#endif