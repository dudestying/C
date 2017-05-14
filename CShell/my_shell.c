#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

extern char **getln();

//I made main an integer but if it shouldnt be, remove
int main() 
{
    int i;
    char **args;

    while(1) 
    {
        printf("\n ~Type Command Here~ \n");
        args = getln();
         
        //this is counting how many arguements we have and printing them
        for(i = 0; args[i] != NULL; i++) 
        {
            printf("Argument %d: %s\n", i, args[i]);
        }

        //this is what happens when nothing is entered in the command line
        if(args[0]==NULL)
        {
            printf("Please enter a command \n");
            continue;
        }
        
        //the help function
        else if(strcmp(args[0], "help") == 0)
        {
            printf("The following commands may be excecuted by this program: \n help, ls, cd, any builtin command with one argument, quit, exit, leave, done \n\n\n");
        }
		
		else if(strcmp(args[0], "who") == 0)
        {
            printf("\n Salma Mobasher is the creator of this awesome (incomplete) program!!! \n");
        
		}
        //this is when someone wants to exit
        else if (strcmp(args[0], "exit") == 0)
        {
            exit(0);
            if(i>1)
            {
                exit(0);
            }
        }
        //this is when someone wants to exit by writing quit
        else if (strcmp(args[0], "quit") == 0)
        {
            exit(0);
            if(i>1)
            {
                exit(0);
            }
        }
        //this is when someone wants to exit by writing leave
        else if (strcmp(args[0], "leave") == 0)
        {
            exit(0);
            if(i>1)
            {
                exit(0);
            }
        }
        //this is when someone wants to exit by writing done
        else if (strcmp(args[0], "done") == 0)
        {
            exit(0);
            if(i>1)
            {
                exit(0);
            }
        }

        pid_t process_id;
	    process_id = fork();
        if (process_id < 0) 
        {
          	printf("The forking process failed....please try again!\n");
           	exit(0);
        } 
	    
		else if (process_id == 0) 
        {
          	process_id = execvp(args[0],args);
            printf("The command you entered is invalid...please enter a valid command!!!\n");
            exit(0);
        } 
		else
        {
            wait(NULL);
        }
		
    }

    return (0);
}
