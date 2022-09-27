// Ball struct
typedef struct {
    int ballRow;
    int ballCol;
    int ballOldRow;
    int ballOldCol;
    int ballWidth;
    int ballHeight;
    int ballRowDirection;
    int ballColDirection;
    unsigned short color;
    int isActive;
} BALL;

// Ball macro
#define MAXBALL 12

// Constants
#define LEFTSCORE 0
#define RIGHTSCORE 0

extern int leftScore;
extern int rightScore;

// Prototypes
void initializeGame();
void initializePaddle();
void initializeBalls();
void updateGame();
void updatePaddle();
void updateBall(BALL* ball);
void collideBalls();
void drawGame();
void drawPaddle();
void drawBalls();
void scoreDisplay();