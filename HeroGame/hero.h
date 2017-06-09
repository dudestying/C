#include <ncurses.h>
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define TRUE 1
#define FALSE 0
#define BOOLEAN int
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )

struct rooms
{
    int roomNum;
    int height;
    int width;
    int xpos;
    int ypos;
    int doorX;
    int doorY;
};

/**
*MakeRooms
*This function parces the rooms, initializes gold count to zero,checks the input file.
*IN: Input file goes in to be read
*OUT: Returns 0 if everything worked
*POST: Creates the room which the game will be played in
*ERROR: If fails then game can not be played
*/
int makeRooms(char*inputFile);

/**
*validPar
*This function verifies there is a valid number (1) of parameters in the command line
*IN: The number of arguments in the command line (numArgc)
*OUT: returns true or false depending on if there is the correct number of parameters
*POST:none
* ERROR: if the number of parameters is false it displays a message then terminates the program.
*/
int validpar(int argcNum);

/**
*buildRoom
*Dynamically allocates the matrix of data for each room. Also draws room borders to the matrix.
*IN: size of each room
*OUT: returns 2D pointer to each room.
*POST: Matrix for the 6 rooms
*ERROR: The program will end if there is an error and a message will appear.
*/
char ** buildRoom(int roomY, int roomX);

/**
*inCheck
*This function checks what key pressed and returns different values based on what element is in the next location.
*IN: Key pressed & current location
*OUT: The element in the next location
*POST: Value determines the next action
*ERROR: no action occurs
*/
int inCheck(char input, int posY, int posX);

/**
*playMove
*Moves the hero to the next location
*IN: input key pressed and current hero location
*OUT: New location
*POST: The hero moves one step (up down right left)
*ERROR: none
*/
void playMove(char input, int * posY, int * posX);

/**
*roomErase
*This cleans up the generated matrix for a room.
*IN: Matrix of one room & it's size
*OUT: none
*POST: Matrix is destroyed (frees memory (dealloccation))
*ERROR: segmentation fault
*/
void roomErase(char** presentRoom, int roomY);
