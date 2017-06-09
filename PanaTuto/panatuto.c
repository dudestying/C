#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*These lines call on functions and declare functions and the arrays which will be used in them.*/
char check4pangram (char UserInput[], char alphaFound[]);
void missingLetters (char alphaFound[]);
char isTutogram (char UserInput[]);

/* This function gets user input and then calls another function called check4pangram to check if the sentence is a pangram, then if it is not, calls another function to print the missing letters.
It then calls a function to verify if the sentence is a tutogram.  */

int main (void)
{
    char MissingLetter= 'N';

    /* This array indicates whether or not each letter of the alphabet is present in the user input. */
    char alphaFound [26] =
    {
        "NNNNNNNNNNNNNNNNNNNNNNNNNN"
    };

    /*We need a variable for the user input!*/
    char UserInput[100];

    printf("Please enter a sentence: ");
    fgets(UserInput,100,stdin);
    printf("The sentence is:\n%s", UserInput);

    MissingLetter = check4pangram(UserInput, alphaFound);

    if(MissingLetter=='N')
    {
        printf("This sentence: %s\n is a panagram.\n", UserInput);
    }
    else
    {
        missingLetters (alphaFound);
    }
    printf("\n");
    if(isTutogram(UserInput)=='Y')
    {
        printf("This is a tutogram!\n");
    }
    else
    {
        printf("This is not a tutogram!\n");
    }
    return 0;
}

/*This function takes the user input and returns an array of y or n for whether or not each letter is present.*/
char check4pangram (char UserInput[], char alphaFound[])
{
    char MissingLetter= 'N';
    int i, j;
    char alphabet[26] =
    {
        "abcdefghijklmnopqrstuvwxyz"
    };

    /*These loops are for comparing the alphabet with each letter of the user input*/
    for(i=0; i<100; i++)
    {
        for (j=0; j<26; j++)
        {
            /*The to lower converts any upper case letters inputted into lower case letter to be scanned!
            This is beasue the alphabet we are comparing it to is lower case so thin input must be converted to be the same.*/
            if(tolower(UserInput[i])==alphabet[j])
            {
                alphaFound[j]= 'Y';
            }
        }
    }
    /* Here the sentece is testing whether or not it is a pangram by checking if any of the array elements are indicated by n. */
    for(j=0; j<26; j++)
    {
        if(alphaFound[j]=='N')
        {
            MissingLetter='Y';
            break;
        }
    }
return (MissingLetter);
}

/*This function is only called if the input is not a pangram. It searches for the n indicating a missing letter and prints out the letter indicated. */
void missingLetters (char alphaFound[])
{
    int j;
    char alphabet[26] =
    {
        "abcdefghijklmnopqrstuvwxyz"
    };
    printf("is not a panagram. \nThe following letters are missing:\n");
    for(j=0; j<26; j++)
    {
        if(alphaFound[j]=='N')
        {
            printf("%c ", alphabet[j]);
        }
    }
}

/*This function takes the user input and verifies that the first letter of each word is similar.*/
char isTutogram (char UserInput[])
{
    /* in the following line, i represents the user input index, j represents the first letter of each word.
    Instead of telling the program to continue until it checks 100 characrters we told it to stop after the end of the inout using "input length" */
    int i=0, j=0, inputLength;
    char isMatching='Y';
    /*This array will contain the first letter of each word and will end with a space*/
    char firstLetter[100];
    inputLength = strlen(UserInput);
    /*The first letter of each word is determined if it is the first letter of the input if it is not a space, or the first letter after a space, if it is not a space.*/
    for(i=0; i<inputLength; i++)
    {
        if((i==0) && (UserInput[i]!=' '))
        {
            firstLetter[j]=tolower(UserInput[i]);
            j=j+1;
        }
        else if(((tolower(UserInput[i]))==' ')&&((tolower(UserInput[i+1]))!=' '))
        {
            firstLetter[j]=tolower(UserInput[i+1]);
            j=j+1;
        }
    }
    /*The space terminates the array of first letters.*/
    firstLetter[j]=' ';
    for(i=0; i<j; i++)
    {
        if((firstLetter[i]!=firstLetter[i+1])&&(firstLetter[i+1]!=' '))
        {
            isMatching='N';
        }
    }
return(isMatching);
}
