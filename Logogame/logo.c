#include "../include/logo.h"

/*This function creates the borders of the windows.
pre:
post:
*/
void borderLine(WINDOW *win);

/*This is the main that calls all the functions and runs the entire program.*/
int main(void)
{
    FILE * saveFile;
    struct object turtle;
    int allX;
    int drawY;
    int promptY=6;
    int distance=0;
    char inCommandLine[62]={' '};
    char inCommandTok[62]={' '};
    char delimiter[2]={' '};
    char *inToken;
    int rotation=0;
	int inColor=0;

    /* Intitalization of the cursor */
    turtle.shape = '^';
    turtle.isPenDown = TRUE;
    turtle.isShowObject = TRUE;
    turtle.rotation = 0;

    /* File handling */
    saveFile = fopen ("assets/a2.txt","w");
    if ( saveFile == NULL )
    {
        printf (" error  opening  file \n");
        exit (0);
    }

    initscr();
    getmaxyx(stdscr, drawY, allX);
    allX = 84;
    drawY= 25;
    /*This is the window where the curser moves*/
    WINDOW *drawWin = newwin(drawY-promptY, allX, 0, 0);
    borderLine(drawWin);
    mvwprintw(drawWin, 1, 20, "Welcome to Salma Mobasher's Logo Interpreter");
    /*This is the window where the prompts are written*/
    WINDOW *promptWin = newwin(promptY, allX, drawY-promptY, 0);
    borderLine(promptWin);

    /* set turtle to home */
    mvwaddch (drawWin,drawY/2, allX/2, turtle.shape);
    turtle.y = drawY/2;
    turtle.x = allX/2;
    wrefresh(drawWin);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4,COLOR_YELLOW, COLOR_BLACK);

    while (1)
    {
        mvwprintw(promptWin, 1, 1, "Valid commands: fd, bk, rt, lt, st, ht, pu, pd, setpencolor, clean, home, bye");
        mvwprintw(promptWin, 2, 1, "Please enter a valid command:");
        mvwprintw(promptWin, 4, 1, "                                                                                 ");
        mvwprintw(promptWin, 4, 1, "? ");
        wgetnstr(promptWin, inCommandLine, 62);
        /*Seperating the inputted strings*/
        strcpy (inCommandTok, inCommandLine);
        inToken = strtok(inCommandTok, delimiter);
        /* skip empty lines */
        if (inToken == NULL)
        {
            continue;
        }
        /************ fd ****************/
        if (strcmp (inToken,"fd") == 0)
        {
            inToken = strtok(NULL, delimiter);
            if (inToken !=NULL)
            {
                distance = atoi(inToken);
                if (turtle.isShowObject == TRUE)
                {
                    mvwaddch (drawWin, turtle.y, turtle.x, ' ');
                }
				switch (turtle.rotation)
                {
                case 0 :
                    turtle.y = turtle.y - distance;
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwvline(drawWin, turtle.y, turtle.x, ACS_VLINE, distance+1);
                    }
                    break;
                case 180 :
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwvline(drawWin, turtle.y, turtle.x, ACS_VLINE, distance+1);
                    }
                    turtle.y = turtle.y + distance;
                    break;
                case 90 :
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwhline(drawWin, turtle.y, turtle.x, ACS_HLINE, distance+1);
                    }
                    turtle.x = turtle.x + distance;
                    break;
                case 270 :
                    turtle.x = turtle.x - distance;
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwhline(drawWin, turtle.y, turtle.x, ACS_HLINE, distance+1);
                    }
                    break;
				default :
                    mvwprintw(promptWin, 3, 1, "rotation not found :  %d              ",turtle.rotation);
                    wrefresh (promptWin);
                    continue;

                }

                if (turtle.isShowObject == TRUE)
                {
                    mvwaddch (drawWin, turtle.y, turtle.x, turtle.shape);
                }
                mvwprintw(promptWin, 3, 1, "? %s                                   ",inCommandLine); 
                wrefresh (drawWin);
                fprintf(saveFile, "%s\n", inCommandLine);
            }
            else
            {
                 mvwprintw(promptWin, 3, 1, "not enough inputs to %s ",inCommandLine);
                 wrefresh (promptWin);
                 continue;
            }
        }
        else
        /****************** bk ***********/
        if (strcmp (inToken,"bk") == 0)
        {
            inToken = strtok(NULL, delimiter);
            if (inToken !=NULL)
            {
                distance = atoi(inToken);
                if (turtle.isShowObject == TRUE)
                {
                    mvwaddch (drawWin, turtle.y, turtle.x, ' ');
                }
                switch (turtle.rotation)
                {
                case 180 :
                    turtle.y = turtle.y - distance;
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwvline(drawWin, turtle.y, turtle.x, ACS_VLINE, distance+1);
                    }
                    break;
                case 0 :
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwvline(drawWin, turtle.y, turtle.x, ACS_VLINE, distance+1);
                    }
                    turtle.y = turtle.y + distance;
                    break;
                case 270 :
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwhline(drawWin, turtle.y, turtle.x, ACS_HLINE, distance+1);
                    }
                    turtle.x = turtle.x + distance;
                    break;
                case 90 :
                    turtle.x = turtle.x - distance;
                    if (turtle.isPenDown == TRUE)
                    {
                        mvwhline(drawWin, turtle.y, turtle.x, ACS_HLINE, distance+1);
                    }
                    break;
			    default :
                    mvwprintw(promptWin, 3, 1, "rotation not found :  %d              ",turtle.rotation);
                    wrefresh (promptWin);
                    continue;

                }

                if (turtle.isShowObject == TRUE)
                {
                    mvwaddch (drawWin, turtle.y, turtle.x, turtle.shape);
                }
                mvwprintw(promptWin, 3, 1, "? %s                                        ",inCommandLine);
                wrefresh (drawWin);
                fprintf(saveFile, "%s\n", inCommandLine);
            }
            else
            {
                 mvwprintw(promptWin, 3, 1, "not enough inputs to %s ",inCommandLine); 
                 wrefresh (promptWin);
                 continue;
           }
        }
        else
        /************ rt ****************/
        if (strcmp (inToken,"rt") == 0)
        {
            inToken = strtok(NULL, delimiter);
            if (inToken !=NULL)
            {
                rotation = atoi(inToken);
                if (rotation != 90)
                {
                     mvwprintw(promptWin, 3, 1, "Only 90 accepted                         ");
                     wrefresh (promptWin);
                     continue;
                }
                turtle.rotation = turtle.rotation + rotation;
				if (turtle.rotation >= 360)
                {
					turtle.rotation = turtle.rotation - 360;
				}
                switch (turtle.shape )
                {
                case '^' :
                    turtle.shape = '>';
                    break;
                case '>' :
                    turtle.shape = 'V';
                    break;
                case 'V' :
                    turtle.shape = '<';
                    break;
                case '<' :
                    turtle.shape = '^';
                    break;
                default :
                    turtle.shape = '>';
                }

                if (turtle.isShowObject == TRUE)
                {
                    mvwaddch (drawWin, turtle.y, turtle.x, turtle.shape);
                    wrefresh (drawWin);
                }

                mvwprintw(promptWin, 3, 1, "? %s                                   ",inCommandLine); 
                fprintf(saveFile, "%s\n", inCommandLine);
            }
            else
            {
                 mvwprintw(promptWin, 3, 1, "not enough inputs to %s ",inCommandLine); 
                 wrefresh (promptWin);
                 continue;
            }
        }
        else
        /************ lt ****************/
        if (strcmp (inToken,"lt") == 0)
        {
            inToken = strtok(NULL, delimiter);
            if (inToken !=NULL)
            {
                rotation = atoi(inToken);
                if (rotation != 90)
                {
                     mvwprintw(promptWin, 3, 1, "Only 90 accepted               ");
                     wrefresh (promptWin);
                     continue;
                }
                turtle.rotation = turtle.rotation - rotation;
			if (turtle.rotation < 0)
                {
				    turtle.rotation = 360 + turtle.rotation;
				}
                switch (turtle.shape )
                {
                case '^' :
                    turtle.shape = '<';
                    break;
                case '<' :
                    turtle.shape = 'V';
                    break;
                case 'V' :
                    turtle.shape = '>';
                    break;
                case '>' :
                    turtle.shape = '^';
                    break;
                default :
                    turtle.shape = '<';
                }

                if (turtle.isShowObject == TRUE)
                {
                    mvwaddch (drawWin, turtle.y, turtle.x, turtle.shape);
                    wrefresh (drawWin);
                }

                mvwprintw(promptWin, 3, 1, "? %s                                   ",inCommandLine);
                fprintf(saveFile, "%s\n", inCommandLine);
            }
            else
            {
                 mvwprintw(promptWin, 3, 1, "not enough inputs to %s ",inCommandLine);
                 wrefresh (promptWin);
                 continue;
            }
        }
        else

        /****************** pu ***********/
        if (strcmp (inToken,"pu") == 0)
        {
            turtle.isPenDown = FALSE;
            fprintf(saveFile, "%s\n", inCommandLine);
        }
        else
        /****************** pd ***********/
        if (strcmp (inToken,"pd") == 0)
        {
            turtle.isPenDown = TRUE;
            fprintf(saveFile, "%s\n", inCommandLine);
        }
        else
        /****************** ht ***********/
        if (strcmp (inToken,"ht") == 0)
        {
            turtle.isShowObject = FALSE;
            mvwaddch (drawWin, turtle.y, turtle.x, ' ');
            wrefresh (drawWin);
            fprintf(saveFile, "%s\n", inCommandLine);
        }
        else
        /****************** st ***********/
        if (strcmp (inToken,"st") == 0)
        {
            turtle.isShowObject = TRUE;
            mvwaddch (drawWin, turtle.y, turtle.x,turtle.shape);
            wrefresh (drawWin);
            fprintf(saveFile, "%s\n", inCommandLine);
        }
        else
        /****************** home ***********/
        if (strcmp (inToken,"home") == 0)
        {
            if (turtle.isShowObject == TRUE)
            {
                mvwaddch (drawWin, turtle.y, turtle.x, ' ');
            }
            if (turtle.isPenDown == TRUE)
                {
                    if (turtle.rotation == 0)
                    {
                        distance = drawY/2  - turtle.y;
                        mvwvline(drawWin, turtle.y, turtle.x, ACS_VLINE, distance+1);
                    }
                    else
                    if (turtle.rotation == 90)
                    {
                        distance = allX/2  - turtle.x;
                        mvwvline(drawWin, turtle.y, turtle.x, ACS_VLINE, distance+1);
                    }
            }
            turtle.rotation = 0;
            turtle.shape = '^';
            if (turtle.isShowObject == TRUE)
            {
                mvwaddch (drawWin,drawY/2, allX/2, turtle.shape);
            }

            turtle.y = drawY/2;
            turtle.x = allX/2;
            wrefresh(drawWin);
            fprintf(saveFile, "%s\n", inCommandLine);
        }
        else
	    /************ setpencolor ****************/
        if (strcmp (inToken,"setpencolor") == 0)
        {
            inToken = strtok(NULL, delimiter);
            if (inToken !=NULL)
            {
				inColor = atoi(inToken);
				switch (inColor)
                {
                case LOGO_COLOR_BLUE :
				    wattron(drawWin, COLOR_PAIR(1));
				    break;
                case LOGO_COLOR_GREEN  :
                    wattron(drawWin, COLOR_PAIR(2));
				    break;
                case LOGO_COLOR_RED  :
				    wattron(drawWin, COLOR_PAIR(3));
				    break;
                case LOGO_COLOR_YELLOW  :
				    wattron(drawWin, COLOR_PAIR(4));
					 break;
				default :
                    mvwprintw(promptWin, 3, 1, "Enter 1 for blue 2 for green 4 for red and 6 for yellow           ");
                    wrefresh (promptWin);
					continue;
				}
				if (turtle.isShowObject == TRUE)
                    {
                        mvwaddch (drawWin, turtle.y, turtle.x, turtle.shape);
                        wrefresh (drawWin);
                    }
				mvwprintw(promptWin, 3, 1, "? %s                                           ",inCommandLine);
                fprintf(saveFile, "%s\n", inCommandLine);

            }
            else
            {
                 mvwprintw(promptWin, 3, 1, "not enough inputs to %s                     ",inCommandLine);
                 wrefresh (promptWin);
                 continue;
            }
        }
		else
        /****************** clean ***********/
        if (strcmp (inToken,"clean") == 0)
        {
            werase(drawWin);
			if (turtle.isShowObject == TRUE)
                    {
                        mvwaddch (drawWin, turtle.y, turtle.x, turtle.shape);
                        borderLine(drawWin);
                    }
			wrefresh (drawWin);
			mvwprintw(promptWin, 3, 1, "? %s                                           ",inCommandLine);
            fprintf(saveFile, "%s\n", inCommandLine);
        }
		else
        if (strcmp (inToken, "bye") == 0)
        {
            break;
        }
        else
        {
            mvwprintw(promptWin, 3, 1, "I don't know how to %s                                                            ",inToken );
            wrefresh (promptWin);
        }

    }

    delwin(drawWin);
    delwin(promptWin);
    endwin();
    fclose(saveFile );
    return(0);
}
