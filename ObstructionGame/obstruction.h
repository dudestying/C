#include <ncurses.h>
#define UP 'i'
#define DOWN 'k'
#define LEFT 'j'
#define RIGHT 'l'
#define TRUE 1
#define FALSE 0
void moveCursor(char direction);
void grid();
void updateData(int * gameData, int x, int y);
int checkFreePosition(int * gameData);
