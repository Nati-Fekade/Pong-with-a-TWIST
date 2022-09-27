#include "gba.h"
#include "game.h"
#include "text.h"
#include "print.h"

// Prototype
void initialize();

void goToStart();
void start();
void goToGame();
void game();
void goToPause();
void pause();
void goToRightWin();
void rightWin();
void goToLeftWin();
void leftWin();

// buttons
unsigned short buttons;
unsigned short oldButtons;

enum {START, GAME, PAUSE, RIGHTWIN, LEFTWIN};
int state;


void initialize() {
    REG_DISPCTL = MODE3 | BG2_ENABLE;

    goToStart();
    // fillScreen(GRAY);
    // //initialize buttons
    // buttons = BUTTONS;
    // oldButtons = 0;
}

void goToStart() {
    fillScreen(MAGENTA);
    int col = (240 - (19 * 6)) / 2;
    drawString(col, 70, "press START to play", WHITE);
    int col2 = (240 - (21 * 6)) / 2;
    drawString(col2, 90, "press SELECT to pause", BLACK);

    state = START;
}

void start() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToGame();
        initializeGame();
    }
}

void goToGame() {
    fillScreen(GRAY);

    state = GAME;
}

void game() {
    updateGame();
    waitForVBlank();
    drawGame();

    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToPause();
    }
    if (leftScore == 5) {
        goToLeftWin();
    }
    if (rightScore == 5) {
        goToRightWin();
    }
}

void goToPause() {
    fillScreen(MAGENTA);
    int col = (240 - (24 * 6)) / 2;
    drawString(col, 70, "press SELECT to continue", WHITE);
    int col2 = (240 - (24 * 6)) / 2;
    drawString(col2, 90, "press START to restart", BLACK);

    state = PAUSE;
}

void pause() {
    if (BUTTON_PRESSED(BUTTON_SELECT)) {
        goToGame();
    }
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}

void goToRightWin() {
    fillScreen(GREEN);
    int col = (240 - (16 * 6)) / 2;;
    drawString(col, 40, "Right Player WON", WHITE);
    int col2 = (240 - (24 * 6)) / 2;
    drawString(col2, 90, "press START to restart", BLACK);
    
    state = RIGHTWIN;
}

void rightWin() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}

void goToLeftWin() {
    fillScreen(BLUE);
    int col = (240 - (15 * 6)) / 2;;
    drawString(col, 70, "Left Player WON", WHITE);
    int col2 = (240 - (24 * 6)) / 2;
    drawString(col2, 90, "press START to restart", BLACK);

    state = LEFTWIN;
}

void leftWin() {
    if (BUTTON_PRESSED(BUTTON_START)) {
        goToStart();
    }
}

int main() {
    mgba_open();

    initialize();

    while(987654321) {
        oldButtons = buttons;
        buttons = BUTTONS;

        switch(state) {
            case START:
                start();
                break;
            case GAME:
                game();
                break;
            case PAUSE:
                pause();
                break;
            case RIGHTWIN:
                rightWin();
                break;
            case LEFTWIN:
                leftWin();
                break;
            default:
                break;
        }
    }
}