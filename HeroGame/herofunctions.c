#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include"../include/hero.h"

//Checks to see if a valid number of items are inputted
int validpar(int argcNum)
{
    if(argcNum!=2)
    {
        printf("You inputted incorrect number of variables! ");
        return 0;
    }
    return TRUE;
}

//Parcing all the elements and placing them where they belong
int makeRooms(char*inputFile)
{
    FILE * inFile;
    char lineIn[150]={' '};
    char inputTok[150]={' '};
    char xDelim[2]={'X'};
    char commaDelim[2]={','};
    char * commaPtr;
    char spaceDelim[2]={' '};
    char winStr[6]={' '};
    char elementStr[6]={' '};
    struct rooms room[6];
    char ** roomData[6];


    int i;
    int maxX;
    int maxY;
    int elementY;
    int elementX;
    char elementSymbol;
    char doorDirection;

    char doorStr[5]={' '};
    int randemMonster;
    char valStr[3]={' '};
    int heroWin;
    int xHero;
    int yHero;
    char inputChar=' ';
    int playerGold;
    int secondRowH;

    //initializing player gold count to 0
    playerGold = 0;


    inFile = fopen(inputFile, "r");

    i = 0;
    if(inFile == NULL)
    {
        printf("error while opening the input file");
        return FALSE;
    }
    initscr();
    noecho();
    curs_set(0);
    getmaxyx(stdscr, maxY, maxX);
    printf ("Max X= %d\nMaxY = %d \n", maxX, maxY);

    //if input file is not empty, true
    while(TRUE)
    {
        if(fgets(lineIn, 150, inFile)==NULL)
        {
            break;
        }
        char *winToken;
        char *tokenIn;
        int elementCount;
        elementCount = 0;
        strcpy(inputTok, lineIn);
        tokenIn = strtok(inputTok, spaceDelim);
        strcpy(winStr, tokenIn);
        winToken = strtok(winStr, xDelim);
        if (winToken !=NULL)
        {
            room[i].height = atoi(winToken)+2;
        }
        winToken = strtok(NULL, xDelim);
        if (winToken !=NULL)
        {
            room[i].width = atoi(winToken)+2;
        }

        //go to next room
        room[i].roomNum = i+1;
        roomData[i] = buildRoom(room[i].height, room[i].width);


        /*** rooms position ***/

        switch (i)
        {
            //first room
            case 0 :
                //positions starting at 2 just so they don't cut get cut off
                room[i].ypos=2;
                room[i].xpos=2;
                break;
            //second and third room have the same cases
            case 1 :
            case 2 :
                //y position same as the first room
                room[i].ypos=2;
                //the side of the one room is 4 spaces away from the room beside it.
                room[i].xpos=room[i-1].xpos+room[i-1].width  + 4;
                break;
            //4th room has different case
            case 3 :
                //second row of the rooms adds 4 from the maximum height of the top row so that they do not overlap
                secondRowH= max(room[0].height,max (room[1].height,room[2].height));
                room[i].ypos=room[0].ypos + secondRowH + 4;
                room[i].xpos=2;
                break;
            //room 5 & 6 have the same cases
            case 4 :
            case 5 :
                room[i].ypos=room[0].ypos + secondRowH + 4;
                room[i].xpos=room[i-1].xpos+room[i-1].width  + 4;
                break;

        }

        /** parse rest of elements **/
        strcpy(inputTok, lineIn);
        tokenIn = strtok(inputTok, spaceDelim);

        while(TRUE)
        {
            tokenIn = strtok(NULL, spaceDelim);
            if (tokenIn == NULL)
            {
                break;
            }
            strcpy(elementStr, tokenIn);
            //cases for inputs from the input file
            switch (elementStr[0])
            {
                case 'd' :
                    doorDirection=elementStr[1];
                    strncpy(doorStr, elementStr+2, 3);
                    //recognizing direction
                    switch (doorDirection)
                    {
                        case 'e' :
                            elementY = atoi(doorStr) + 1;
                            elementX = room[i].width -1;
                            break;
                        case 'w' :
                            elementY = atoi(doorStr) + 1;
                            elementX = 0;
                            break;
                        case 'n' :
                            elementY = 0;
                            elementX = atoi(doorStr) + 1;
                            break;
                        case 's' :
                            elementY = room[i].height -1;
                            elementX = atoi(doorStr) + 1;
                            break;
                    }
                    room[i].doorY=elementY;
                    room[i].doorX=elementX;
                    elementSymbol = '+';
                    roomData[i][elementY][elementX]=elementSymbol;
                case 'h' :
                    elementSymbol = '@';
                    heroWin = i + 1;
                    break;
                case 'z' :
                    elementSymbol = '<';
                    break;
                case 'a' :
                    elementSymbol = '>';
                    break;
                case 'g' :
                    elementSymbol = '*';
                    break;
                case 'G' :
                    elementSymbol = '8';
                    break;
                case 'w' :
                    elementSymbol = ')';
                    break;
                case 'W' :
                    elementSymbol = '(';
                    break;
                case 'm' :
                    //randimizing monsters!
                    randemMonster = rand() % 4;
                    switch (randemMonster)
                    {
                        case 0 :
                            elementSymbol = 'A';
                            break;

                        case 1 :
                            elementSymbol = 'B';
                            break;
                        case 2 :
                            elementSymbol = 'S';
                            break;
                        case 3 :
                            elementSymbol = 'Z';
                            break;
                    }
                    break;
                case 'e' :
                    elementSymbol = ']';
                    break;
                case 'M' :
                    elementSymbol = 'T';
                    break;
                case 'p' :
                    elementSymbol = '!';
                    break;
            }
            //counting how many elements are there not including the doors
            if (elementStr[0]!='d')
            {
                elementCount++;
                if (elementCount > 10)
                {
                    mvwprintw(stdscr, maxY -2, 0, "Max element Count exceeded \n");
                    break;
                }
                strncpy(doorStr, elementStr+1, 5);
                elementY = atoi(doorStr) + 1;
                commaPtr = strstr(doorStr, commaDelim);
                commaPtr++;
                strcpy(valStr, commaPtr);
                elementX = atoi(valStr) + 1;

                roomData[i][elementY][elementX]=elementSymbol;
                if (elementStr[0]=='h')
                {
                    yHero=elementY+room[heroWin-1].ypos;
                    xHero=elementX+room[heroWin-1].xpos;
                }
            }

        /** print rooms **/
            for (int j=0;j<room[i].height; j++)
            {
                for (int k=0;k<room[i].width; k++)
                {
                    mvaddch(j+room[i].ypos,k +room[i].xpos,roomData[i][j][k]);
                }
            }

        }
        i++;
    }
    if (secondRowH + max(room[3].height,max (room[4].height,room[5].height)) + 6 > maxY)
    {
        mvwprintw(stdscr, 0, 0, "Window hight too low\n");
        getch();
        endwin();
        printf( "The player gold value = %d \n", playerGold);
        for (i=0;i<6;i++)
        {
             roomErase(roomData[i], room[i].height);
        }
        fclose(inFile);
        return 0;
    }


    /** start the game **/
    heroWin = 1;
    move(yHero,xHero);
    while (inputChar !='q')
    {
        int condition;
        condition = 0;
        inputChar = getch();
        condition = inCheck(inputChar, yHero, xHero);
        if (condition== 2)
        {
            break;
        }
        if (condition == 1)
        {
            playMove(inputChar,&yHero,&xHero);
            mvaddch(yHero, xHero, '@');
            move(yHero, xHero);
        }
        else if    (condition == 3)
        {
            if(heroWin == 6)
            {
                heroWin = 1;
            }
            else
            {
                heroWin++;
            }
            mvaddch(yHero, xHero, '.');
            yHero=room[heroWin-1].doorY+room[heroWin-1].ypos,
            xHero=room[heroWin-1].doorX+room[heroWin-1].xpos;
            move(yHero, xHero);
        }
        else if    (condition == 4)
        {
            playerGold = playerGold + rand() % 51;
            playMove(inputChar,&yHero,&xHero);
            mvaddch(yHero, xHero, '@');
            move(yHero, xHero);

        }
        else if    (condition == 5)
        {
            playerGold = playerGold + 50 + rand() % 201;
            playMove(inputChar,&yHero,&xHero);
            mvaddch(yHero, xHero, '@');
            move(yHero, xHero);

        }

        refresh();


    }
    refresh();
    endwin();
    printf( "The player gold value = %d \n", playerGold);
    for (i=0;i<6;i++)
    {
        roomErase(roomData[i], room[i].height);
    }
    fclose(inFile);
    return 0;
}

//This builds the rooms
char ** buildRoom(int roomY, int roomX)
{
    char ** presentRoom;

    presentRoom = malloc(sizeof(char*)*roomY);
    if (presentRoom == NULL)
    {
        printf("Failed to print");
        exit(1);
    }

    for (int i = 0;i<=roomY;i++)
    {
        presentRoom[i] = malloc(sizeof(char)*roomX);
        if (presentRoom[i] == NULL)
        {
            printf("failed");
            exit(1);
        }

    }
    for (int i=1;i<roomY-1;i++)
    {
        for (int k=1;k<roomX-1;k++)
        {
            presentRoom[i][k] = '.';
        }

        for (int i=0; i<roomX; i++)
        {
            presentRoom[0][i] = '-';
        }

        for (int i=0;i<roomX; i++)
        {
            presentRoom[roomY-1][i] = '-';
        }

        for (int i=0;i<roomY;i++)
        {
            presentRoom[i][0] = '|';
        }

        for (int i=0;i<roomY;i++)
        {
            presentRoom[i][roomX-1] = '|';
        }
    }
    return presentRoom;
}


 //check for given inputs to see if the player can move or not
int inCheck(char input, int yPoint, int xPoint)
{
    char space = ' ';

    switch(input)
    {
        case 'w':
            yPoint -= 1;
            break;
        case 'a':
            xPoint -= 1;
            break;
        case 's':
            yPoint += 1;
            break;
        case 'd':
            xPoint += 1;
            break;
        default:
            return 0;
    }

    space = mvinch(yPoint,xPoint) &A_CHARTEXT;
    switch(space)
    {
        case '|':
        case '-':
        case ' ':
        case 'A':
        case 'B':
        case 'S':
        case 'Z':
        case 'T':
            return 0;
            break;

        case '.':
            return 1;
            break;
        case '>':
        case '<':
            return 2;
        case '+':
            return 3;
            break;
        case '*':
            return 4;
            break;
        case '8':
            return 5;
            break;

        default:
            return 1;
    }
    return 0;
}

//This makes the player move
void playMove(char input, int * yPoint, int * xPoint)
{
    switch(input)
    {
        case 'w':
            if(mvinch(*yPoint,*xPoint) != '+')
            {
                mvaddch(*yPoint, *xPoint, '.');
            }
            *yPoint -= 1;
        break;

        case 'a':
            if(mvinch(*yPoint,*xPoint) != '+')
            {
                mvaddch(*yPoint, *xPoint, '.');
            }
            *xPoint -= 1;
            break;
        case 's':
            if(mvinch(*yPoint,*xPoint) != '+')
            {
                mvaddch(*yPoint, *xPoint, '.');
            }
            *yPoint += 1;
            break;
        case 'd':
            if(mvinch(*yPoint,*xPoint) != '+')
            {
                mvaddch(*yPoint, *xPoint, '.');
            }
            *xPoint += 1;
            break;

        default:
            return;
    }
    mvaddch(*yPoint, *xPoint, '@');
}

//This destroys the rooms
void roomErase(char ** presentRoom, int roomY)
{
    for (int i=0; i<roomY; i++)
    {
        free(presentRoom[i]);
  }
    return;
}
