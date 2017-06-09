#include "../include/obstruction.h"
#include <stdlib.h>
#include <string.h>

/*The main contains the main components of the game.*/
int main()
{
    char inputChar;
    char p1Name[50]={' '};
    char p2Name[50]={' '};
    int gameData[36]={0};
    int player=1;
    int x;
    int y;
    int firstFree;

    initscr();
    start_color();
    cbreak ();
    grid();
    init_pair(1,COLOR_RED, COLOR_RED);
    init_pair(2,COLOR_GREEN, COLOR_BLACK);
    init_pair(3,COLOR_CYAN, COLOR_BLACK);
    /*The following prints all the initial words on the screen.*/
    mvwprintw(stdscr, 0, 15, "How to play the game:");
    mvwprintw(stdscr, 1, 15, "This is a two player game.");
    mvwprintw(stdscr, 2, 15, "Each player takes turns marking a spot on the board.");
    mvwprintw(stdscr, 3, 15, "No position directly surrounding a selected spot can be marked.");
    mvwprintw(stdscr, 4, 15, "The last player able to make a move wins the game.");
    mvwprintw(stdscr, 5, 15, "Press q twice to quit once the names are entered.");

    mvwprintw(stdscr, 15, 0, "Please enter the name of player 1: ");
    getstr(p1Name);
    mvwprintw(stdscr, 17, 0, "Welcome, %s", p1Name);
    mvwprintw(stdscr, 19, 0, "Please enter the name of player 2: ");
    getstr(p2Name);
    mvwprintw(stdscr, 21, 0, "Welcome, %s", p2Name);
    mvwprintw(stdscr, 23, 0, "Press any key to continue");
    getch();

    mvwprintw(stdscr, 15, 0, "It is %s's turn to play first. Use the ijkl keys to move and press x to select.                        ", p1Name);
    mvwprintw(stdscr, 17, 0, "                                                                           ");
    mvwprintw(stdscr, 19, 0, "                                                                        ");
    mvwprintw(stdscr, 21, 0, "                                                                               ");
    mvwprintw(stdscr, 23, 0, "                                                                          ");

    refresh();
    noecho ();
    move(1,1);

    inputChar = getch();
    /*playing the game as long as quit is not pressed.*/
    while (inputChar !='q')
    {
        moveCursor(inputChar);
        inputChar = getch();
        /*Conditions for player one*/
        if ((inputChar=='x')&&(player==1))
        {
            getyx(stdscr,y,x);
            /*The equation is to convert from coordinates on screen 
            to coordinates on grid.*/
            if (gameData[(y-1)/2+6*(x-1)/2]==0)
            {
                gameData[(y-1)/2+6*(x-1)/2]=1;
                updateData(gameData, (x-1)/2, (y-1)/2);
                firstFree=checkFreePosition(gameData);
                /*When firstFree is -1, there are no more empty spots on the grid*/
                if (firstFree==-1)
                {
                    attron(COLOR_PAIR(2));
                    mvaddch(y,x, 'x');
                    mvwprintw(stdscr, 15,0, "%s is the winner!             \n", p1Name);
                    refresh();
                    break;
                }
                else
                {
                    player=2;
                    attron(COLOR_PAIR(2));
                    mvwprintw(stdscr, 15, 0, "It is now %s's turn! Use the ijkl keys to move and press o to select.                   ", p2Name);
                    mvaddch(y,x, 'x');
                    /*Moving the cursor to the first available position*/
                    x=(firstFree/6)*2+1;
                    y=(firstFree%6)*2+1;
                    move(y,x);
                    refresh();
                }
            }
        }
        /*Conditions for player 2*/
        if ((inputChar=='o')&&(player==2))
        {
            getyx(stdscr,y,x);
            if (gameData[(y-1)/2+6*(x-1)/2]==0)
            {
                gameData[(y-1)/2+6*(x-1)/2]=2;
                updateData(gameData, (x-1)/2, (y-1)/2);
                firstFree=checkFreePosition(gameData);
                if (firstFree==-1)
                {
                    attron(COLOR_PAIR(3));
                    mvaddch(y,x, 'o');
                    mvwprintw(stdscr, 15,0, "%s is the winner!              \n", p2Name);
                    refresh();
                    break;
                }

                else
                {
                    player=1;
                    attron(COLOR_PAIR(3));
                    mvwprintw(stdscr, 15, 0, "It is now %s's turn! Use the ijkl keys to move and press x to select.                    ", p1Name);
                    mvaddch(y,x, 'o');
                    x=(firstFree/6)*2+1;
                    y=(firstFree%6)*2+1;
                    move(y,x);
                    refresh();
                }
            }
        }
        refresh();
    }


    refresh();
    getch();
    endwin();
    return(0);
}


/*This function makes the ijkl move the cursor.*/
void  moveCursor(char direction)
{
    int x, y;
    getyx(stdscr, y,x);
    switch (direction)
    {
        case UP:
        if (y>0)
        {
            y=y-2;
        }
        break;
        case DOWN:
        if (y<11)
        {
            y=y+2;
        }
        break;
        case RIGHT:
        if (x<11)
        {
            x=x+2;
        }
        break;
        case LEFT:
        if (x>2)
        {
            x=x-2;
        }
        break;

    }
    move(y,x);
}

/*This function draws the grid!!!*/
void grid()
{
    int i;
    int j;
    for (i=0; i<=12; i=i+2)
    {
        for (j=0; j<=12;j++)
        {
            mvaddch(j,i, '|' );
        }
    }
    for (i=0; i<=12; i=i+2)
    {
        for (j=0; j<=12;j++)
        {
            mvaddch(i,j, '-' );
        }
    }
    move(1,1);
}

/*This function check for empty spaces on the grid*/
int checkFreePosition(int * gameData)
{
    int i;
    for (i=0; i<=35; i++)
    {
        if (gameData[i]==0)
        {
            return(i);
        }
    }
    /*If this returns -1 then the game is over and there are no more free spaces.*/
    return (-1);
}

/*This function marks the areas surrounding the selected box and highlights them.*/
void updateData(int * gameData, int x, int y)
{
    attron(COLOR_PAIR(1));
    /* Above*/
    if (y>0)
    {
        gameData[y+6*x-1]=3;
        mvaddch((y-1)*2+1,x*2+1, ' ');
    }
    /* Below*/
    if (y<5)
    {
        gameData[y+6*x+1]=3;
        mvaddch((y+1)*2+1,x*2+1, ' ');
    }
    /*Right*/
    if (x<5)
    {
        gameData[y+6*x+6]=3;
        mvaddch(y*2+1,(x+1)*2+1, ' ');
    }
    /* Left*/
    if (x>0)
    {
        gameData[y+6*x-6]=3;
        mvaddch(y*2+1,(x-1)*2+1, ' ');
    }
    /* above left*/
    if ((x>0)&&(y>0))
    {
        gameData[y+6*x-7]=3;
        mvaddch((y-1)*2+1,(x-1)*2+1, ' ');
    }
    /* Above right*/
    if ((x<5)&&(y>0))
    {
        gameData[y+6*x+5]=3;
        mvaddch((y-1)*2+1,(x+1)*2+1, ' ');
    }
    /* Below right*/
    if ((x<5 )&&(y<5))
    {
        gameData[y+6*x+7]=3;
        mvaddch((y+1)*2+1,(x+1)*2+1, ' ');
    }
    /* Below left*/
    if ((x>0)&&(y<5))
    {
        gameData[y+6*x-5]=3;
        mvaddch((y+1)*2+1,(x-1)*2+1, ' ');
    }
}
