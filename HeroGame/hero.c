#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include"hero.h"

int main(int argc, char*argv[])
{
    if(validpar(argc)==FALSE)
    {
        return FALSE;
    }
    if(makeRooms(argv[1])==FALSE)
    {
        return FALSE;
    }
}
