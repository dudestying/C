#ifndef _SMOBASHE_A2H
#define _SMOBASHE_A2H

#include <ncurses.h>
#define TRUE 1
#define FALSE 0
#define BOOLEAN int

#define COLOR_BLACK 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_YELLOW 3
#define COLOR_BLUE 4
#define COLOR_WHITE 7

#define LOGO_COLOR_RED 4
#define LOGO_COLOR_GREEN 2
#define LOGO_COLOR_YELLOW 6
#define LOGO_COLOR_BLUE 1

#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include<curses.h>
#include<unistd.h>
#include <stdlib.h>

struct object
{
    int x;
    int y;
    char shape;
    BOOLEAN isPenDown;
    BOOLEAN isShowObject;
    int rotation;
};
void borderLine(WINDOW *win);

#endif
