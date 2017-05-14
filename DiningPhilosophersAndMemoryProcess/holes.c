#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked.h"

int main(int argc, char *argv[]) {
    int sizes [1000];
    char identify [1000];
    int size = 0;
    int theSize = 0;
    int i = 0;
    char type;
    //Init an array for passing to all the functons
    while (1) {
        if (fscanf(stdin, "%s %d", &type, &size) != EOF) {
            sizes[i] = size;
            identify[i] = type;
            i = i + 1;
        } else {
            theSize = i;
            break;
        }
    }

    //Run all functions

    fFit(sizes, identify, theSize);
    nFit(sizes, identify, theSize);
    bFit(sizes, identify, theSize);
    wFit(sizes, identify, theSize);

    return 0;
}

void bFit(int * sizes, char * identify, int theSize) {

    int memSize = 128;
    int numProc = 1;

    //Free mem= - 
    //Used mem= letter
    char procA [memSize];
    for (int i = 0; i < theSize; i++) {
        addToBack(sizes[i], identify[i], 0, 0, 0);
        numProc++;
    }
    //Set Array to Empty
    for (int i = 0; i < memSize; i++) {
        procA[i] = '-';
    }
    //memPrint(procA);
    addNext(procA, numProc);
}

void wFit(int * sizes, char * identify, int theSize) {
    int memSize = 128;
    int numProc = 1;

    //Free mem= - 
    //Used mem= letter
    char procA [memSize];
    for (int i = 0; i < theSize; i++) {
        addToBack(sizes[i], identify[i], 0, 0, 0);
        numProc++;
    }
    //Set Array to Empty
    for (int i = 0; i < memSize; i++) {
        procA[i] = '-';
    }
    //memPrint(procA);
    addNext(procA, numProc);
}

void nFit(int * sizes, char * identify, int theSize) {
    int memSize = 128;
    int numProc = 1;

    //Free mem= - 
    //Used mem= letter
    char procA [memSize];
    for (int i = 0; i < theSize; i++) {
        addToBack(sizes[i], identify[i], 0, 0, 0);
        numProc++;
    }
    //Set Array to Empty
    for (int i = 0; i < memSize; i++) {
        procA[i] = '-';
    }
    //memPrint(procA);
    addNext(procA, numProc);
}
void fFit(int * sizes, char * identify, int theSize) {
    int memSize = 128;
    int numProc = 1;

    //Free mem= - 
    //Used mem= letter
    char procA [memSize];
    for (int i = 0; i < theSize; i++) {
        addToBack(sizes[i], identify[i], 0, 0, 0);
        numProc++;
    }
    //Set Array to Empty
    for (int i = 0; i < memSize; i++) {
        procA[i] = '-';
    }
    addNext(procA, numProc);


}

//Display memory visually
void memPrint(char * procA) {
    for (int i = 0; i < 128; i++) {
        if (i % 32 == 0 && i != 0)
            printf("\n");
        printf("%c", procA[i]);

    }
    printf("\n\n");
}

void addNext(char * procA, int numProc) {
    //Variables for Log
    double static cumCount = 0;
    double static totalMem = 0;
    double static totalLoads = 0;
    double static totalCumCount = 0;
    double static totalHoles = 0;
    while (1) {
        int numProMem = 0;
        int holes = 0;
        double memusage = 0;
        double cum = 0;
        holes = checkHoles(procA);
        numProMem = checkProc(procA);
        memusage = checkMem(procA);
        memusage = (memusage / 128)*100;
        totalMem = totalMem + memusage;
        cum = (totalMem / cumCount);

        //Print out log

        printf("Pid loaded, #processes = %d, #holes = %d, %%memusage = %.2lf, cumulative %%mem = %.2lf \n", numProMem, holes, memusage, cum);
        cumCount++;
        totalHoles = totalHoles + holes;
        totalCumCount = totalCumCount + (totalMem / cumCount);
        totalLoads = totalLoads + numProMem;
        memPrint(procA);
        int done = 0;
        //Check to see if all process works 3x
        done = checkNumArray(numProc);
        static int old;
        if (done != 0) {
            display();
            break;
        } 
        //Add proccess to memory
        else {
            int freeMem = 0;
            int offset;

            for (int i = 0; i < 128; i++) {
                if (procA[i] == '-') {
                    offset = i;
                    break;
                }
            }
            for (int i = 0; i < 128; i++) {
                if (procA[i] == '-') {
                    freeMem += 1;
                }
                if (procA[i] != '-') {
                    break;
                }
            }
            struct Node node;
            node = getFront();
            //If free memory is too small, remove oldest memory
            if (node.inData + offset > 128) {

                {
                    rMem(procA, node);
                }
                if (freeMem < node.inData) {
                    rMem(procA, node);
                }
                //If memory has enough space, add it to the end of the previous element
            } else {
                for (int j = offset; j < (node.inData + offset); j++) {
                    procA[j] = node.identify;
                }
                removeFromFront();
                if (node.works < 3) {
                    addToBack(node.inData, node.identify, offset, (node.works + 1), (old + 1));
                }
                old++;
            }

        }

    }
    //Print after loop is done
    printf("Total loads =%.0lf, average #processes = %.2lf \naverage #holes = %.2lf, cumulative %%mem =%.2lf \n\n", (totalLoads),
            (totalLoads / cumCount), (totalHoles / cumCount), (totalCumCount / cumCount));
}

void rMem(char * procA, struct Node cNode) {

    int fMem = 0;
    struct Node node;
    struct Node nRemove;
    struct Node nNode;

    //Find Oldest
    node = getFront();
    nRemove = getRemove();

    //Remove oldest
    for (int i = nRemove.position; i < (nRemove.inData + nRemove.position); i++) {
        procA[i] = '-';
    }

    nNode = lookUp(nRemove.identify);
    changeOld(nNode.identify);

    //Check free memory again
    for (int i = 0; i < 128; i++) {
        if (procA[i] == '-') {
            fMem++;
            //Find the holes
        } else if (procA[i] != '-') {

            break;
        }
    }
    //Recursivly call itself untill there is enough free memory
    if (fMem < node.inData) {

        rMem(procA, node);
    }
}