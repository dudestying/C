#include <stdio.h>
#include <stdlib.h>
#include "linked.c"


void addToBack(int value, char identify, int position, int works, int isOld);

struct Node lookUp(char identify);

struct Node getRemove();

void setRan(int works);

struct Node getFront();

struct Node getBack();

int checkNumArray(int numProc);

int checkMem(char * procA);

int checkHoles(char * procA);

int checkProc(char * procA);

void changeOld(char identify);

void addToFront(int value);

void setValues(int works, int position);

void removeFromFront();

void killList();

void removeFromBack();

int display();

void bFit(int * sizes, char * identify, int theSize);

void wFit(int * sizes, char * identify, int theSize);

void nFit(int * sizes, char * identify, int theSize);

void fFit(int * sizes, char * identify, int theSize);

void memPrint(char * procA);

void addNext(char * procA, int numProc);

void rMem(char * procA, struct Node cNode);