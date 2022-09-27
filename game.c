#include "gba.h"
#include "game.h"
#include "print.h"

// variables
int leftPaddleWidth;
int leftPaddleHeight;
int leftPaddleRow, leftPaddleOldRow;
int leftPaddleCol, leftPaddleOldCol;

int rightPaddleWidth;
int rightPaddleHeight;
int rightPaddleRow, rightPaddleOldRow;
int rightPaddleCol, rightPaddleOldCol;

int horizontalCol, horizontalRow, horizontalSize;

int leftScore;
int rightScore;

BALL balls[MAXBALL];

void initializeGame() {
    initializePaddle();
    initializeBalls();

    // initialize scores
    leftScore = LEFTSCORE;
    rightScore = RIGHTSCORE;

    // initialize horizontal
    horizontalCol = 0;
    horizontalRow = 10;
    horizontalSize = SCREENWIDTH;
}

void initializePaddle() {
    // initialize right paddle
    rightPaddleWidth = 3;
    rightPaddleHeight = 30;
    rightPaddleRow = (SCREENHEIGHT / 2) - (rightPaddleHeight / 2);
    rightPaddleCol = SCREENWIDTH - rightPaddleWidth;
    rightPaddleOldRow = rightPaddleRow;
    rightPaddleOldCol = rightPaddleCol;

    // initialize left paddle
    leftPaddleWidth = 3;
    leftPaddleHeight = 30;
    leftPaddleRow = (SCREENHEIGHT / 2) - (leftPaddleHeight / 2);
    leftPaddleCol = 0;
    leftPaddleOldRow = leftPaddleRow;
    leftPaddleOldCol = leftPaddleCol;
}

void initializeBalls() {
    // initialize ball
    for (int i = 0; i < MAXBALL; i++) {
        balls[i].ballCol = SCREENWIDTH / 2;
        balls[i].ballRow = SCREENHEIGHT / 2;
        balls[i].ballHeight = 3;
        balls[i].ballWidth = 3;
        balls[i].ballRowDirection = 1;
        balls[i].ballColDirection = 1;

        balls[i].isActive = 0;
    }
    balls[11].isActive = 1;
}

void updateGame() {
    updatePaddle();

    for (int i = 0; i < MAXBALL; i++) {
        if (balls[i].isActive) {
            updateBall(&(balls[i]));
        }
    }
}

void updatePaddle() {
    if (leftPaddleRow < horizontalRow) { // Top Left Paddle
        leftPaddleOldRow = leftPaddleRow;
        leftPaddleRow = horizontalRow;
    }
    if ((leftPaddleRow + leftPaddleHeight > SCREENHEIGHT)) { // Bottom Left Paddle
        leftPaddleOldRow = leftPaddleRow;
        leftPaddleRow = (SCREENHEIGHT - 1) - (leftPaddleHeight - 1);
    }
    if (rightPaddleRow < horizontalRow) { // Top Right Paddle
        rightPaddleOldRow = rightPaddleRow;
        rightPaddleRow = horizontalRow;
    }
    if (rightPaddleRow + rightPaddleHeight > SCREENHEIGHT) { // Bottom Right Paddle
        rightPaddleOldRow = rightPaddleRow;
        rightPaddleRow = (SCREENHEIGHT - 1) - (rightPaddleHeight - 1);
    }

    if (BUTTON_HELD(BUTTON_A)) { // Left Paddle Go UP
        leftPaddleRow--;
    }
    if (BUTTON_HELD(BUTTON_B)) { // Left Paddle Go DOWN
        leftPaddleRow++;
    }
    if (BUTTON_HELD(BUTTON_UP)) { // Right Paddle Go UP
        rightPaddleRow--;
    }
    if (BUTTON_HELD(BUTTON_DOWN)) { // Right Paddle Go DOWN
        rightPaddleRow++;
    }
}


void updateBall(BALL* ball) {
    //make ball bounce off of edges towards opposite direction of the screen
    if (ball->ballRow <= horizontalRow || ball->ballRow + ball->ballHeight - 1 > SCREENHEIGHT - 1) {
        ball->ballRowDirection *= -1;
    }
    if (ball->ballCol == 0) {
        ball->ballColDirection *= -1;
        rightScore++;
        mgba_printf("left score: %d", rightScore);
    }
    if (ball->ballCol + ball->ballWidth - 1 > SCREENWIDTH - 2) {
        ball->ballColDirection *= -1;
        leftScore++;
        mgba_printf("right score: %d", leftScore);
    }

    if (collision(ball->ballCol, ball->ballRow, ball->ballWidth, ball->ballHeight, leftPaddleCol, leftPaddleRow, leftPaddleWidth, leftPaddleHeight)) {
        mgba_printf("left collision");
        ball->ballColDirection *= -1;
        for (int j = 0; j < MAXBALL; j++) {
            if (balls[j].isActive == 0) {
                balls[j].isActive = 1;
                mgba_printf("inside left for-loop");

                balls[j].ballCol = ball->ballCol + 2;
                balls[j].ballRow = ball->ballRow;

                
                balls[j].ballRowDirection = ball->ballRowDirection * -1;
                balls[j].ballColDirection = ball->ballColDirection;
                
                break;
            }
        }
    }
    if (collision(ball->ballCol, ball->ballRow, ball->ballWidth, ball->ballHeight, rightPaddleCol, rightPaddleRow, rightPaddleWidth, rightPaddleHeight)) {
        mgba_printf("right collision");
        ball->ballColDirection *= -1;
        for (int j = 0; j < MAXBALL; j++) {
            if (balls[j].isActive == 0) {
                balls[j].isActive = 1;
                mgba_printf("inside right for-loop");

                balls[j].ballCol = ball->ballCol - 2;
                balls[j].ballRow = ball->ballRow;

                balls[j].ballColDirection = ball->ballColDirection;
                balls[j].ballRowDirection = ball->ballRowDirection * -1;
                
                break;
            }
        }
    }
    //update ball position
    ball->ballRow += ball->ballRowDirection;
    ball->ballCol += ball->ballColDirection;
}

void drawGame() {
    drawPaddle();
    drawBalls();
    scoreDisplay();
}

void drawPaddle() {
    // Draw middle and top boundary line
    drawRectangle((SCREENWIDTH / 2), 0, 5, SCREENHEIGHT, WHITE);
    drawHorizontal(horizontalCol, horizontalRow, horizontalSize, WHITE);

    // Erase Previous Paddles
    drawRectangle(leftPaddleOldCol, leftPaddleOldRow, leftPaddleWidth, leftPaddleHeight, GRAY);
    drawRectangle(rightPaddleOldCol, rightPaddleOldRow, rightPaddleWidth, rightPaddleHeight, GRAY);
    // Draw Paddles
    drawRectangle(leftPaddleCol, leftPaddleRow, leftPaddleWidth, leftPaddleHeight, BLUE);
    drawRectangle(rightPaddleCol, rightPaddleRow, rightPaddleWidth, rightPaddleHeight, GREEN);

    leftPaddleOldRow = leftPaddleRow;
    leftPaddleOldCol = leftPaddleCol;

    rightPaddleOldCol = rightPaddleCol;
    rightPaddleOldRow = rightPaddleRow;
}

void drawBalls() {
    for (int i = 0; i < MAXBALL; i++) {
        if (balls[i].isActive) {
            // Erase ball
            drawRectangle(balls[i].ballOldCol, balls[i].ballOldRow, balls[i].ballWidth, balls[i].ballHeight, GRAY);
            // Draw ball
            drawRectangle(balls[i].ballCol, balls[i].ballRow, balls[i].ballWidth, balls[i].ballHeight, RED);
        
            balls[i].ballOldRow = balls[i].ballRow;
            balls[i].ballOldCol = balls[i].ballCol;
        }
    }
}

void scoreDisplay() {
    if (leftScore == 1) {
        drawRectangle(30, 1, 3, 8, CYAN);
    }
    if (leftScore == 2) {
        drawRectangle(40, 1, 3, 8, CYAN);
    }
    if (leftScore == 3) {
        drawRectangle(50, 1, 3, 8, CYAN);
    }
    if (leftScore == 4) {
        drawRectangle(60, 1, 3, 8, CYAN);
    }
    if (leftScore == 5) {
        drawRectangle(70, 1, 3, 8, CYAN);
    }

    if (rightScore == 1) {
        drawRectangle(190, 1, 3, 8, CYAN);
    }
    if (rightScore == 2) {
        drawRectangle(200, 1, 3, 8, CYAN);
    }
    if (rightScore == 3) {
        drawRectangle(210, 1, 3, 8, CYAN);
    }
    if (rightScore == 4) {
        drawRectangle(220, 1, 3, 8, CYAN);
    }
    if (rightScore == 5) {
        drawRectangle(230, 1, 3, 8, CYAN);
    }
}