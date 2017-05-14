#include <stdio.h>
#include <stdlib.h>

struct Node {
    int inData;
    char identify;
    int works;
    int position;
    int old;
    struct Node* nextPtr;
} *rear, *front, Node;

void addToBack(int value, char identify, int position, int works, int old) {
    struct Node *temp;
    temp = (struct Node *) malloc(sizeof (struct Node));
    temp->inData = value;
    temp->identify = identify;
    temp->position = position;
    temp->works = works;
    temp->old = old;
    if (front == NULL) {
        front = temp;
        front->nextPtr = NULL;
        rear = front;
    } else {
        front->nextPtr = temp;
        front = temp;
        front->nextPtr = NULL;
    }
}

struct Node lookUp(char identify) {
    struct Node *temp = rear;
    while (temp != NULL) {
        if (temp->identify == identify) {
            // found it!
            return *temp;
            break;
        }
        temp = temp->nextPtr;
    }
    return * temp->nextPtr;
}

struct Node getRemove() {
    int min = 999;
    struct Node *oldNode;
    struct Node *temp = rear;
    while (temp != NULL) {
        if (temp->old < min && temp->old != 0 && temp->works >= 1) {
            min = temp->old;
            oldNode = temp;
        }
        temp = temp->nextPtr;
    }
    return *oldNode;
}

void setRan(int works) {
    struct Node *currentPtr = rear;
    currentPtr->works = works;

}

struct Node getFront() {
    struct Node *currentPtr = rear;
    return *currentPtr;

}

struct Node getBack() {
    struct Node *currentPtr = front;
    return *currentPtr;

}

int checkNumArray(int numProc) {
    int works = 1;
    struct Node *temp = rear;
    while (temp != NULL) {
        if (temp->works == 3) {
            works = works + 1;
        }
        temp = temp->nextPtr;
    }
    if (works == numProc) {
        return 1;
    } else {
        return 0;
    }

}

int checkMem(char * procA) {
    int numPro = 0;
    for (int i = 0; i < 128; i++) {
        if (procA[i] != '-') {
            numPro++;
        }
    }
    return numPro;
}

int checkHoles(char * procA) {
    int endFound = 0;
    int numHoles = 1;
    for (int i = 0; i < 128; i++) {

        if (procA[i] == '-') {
            for (int j = i; j < 128; j++) {
                if (procA[j] != '-' && procA[j + 1] != '-') {
                    endFound++;
                }

            }
            if (endFound == 1) {
                numHoles++;
            }
        }


    }
    if (numHoles > 4)
        numHoles = 2;

    return numHoles;
}

int checkProc(char * procA) {
    int numPro = 0;
    struct Node *temp = rear;
    while (temp != NULL) {
        for (int i = 0; i < 128; i++) {
            if (temp->identify == procA[i] && procA[i] != procA[i + 1]) {
                numPro++;
            }
        }

        temp = temp->nextPtr;

    }

    return numPro;
}

void changeOld(char identify) {
    int max = 0;
    struct Node *lTemp = rear;
    while (lTemp != NULL) {
        if (lTemp->old > max && lTemp->old != 0 && lTemp->works >= 1) {
            max = lTemp->old;
        }
        lTemp = lTemp->nextPtr;
    }
    struct Node *temp = rear;
    while (temp != NULL) {
        if (temp->identify == identify) {
            // found it!
            temp->old = temp->old + max + 1;
            break;
        }
        temp = temp->nextPtr;
    }

}

void addToFront(int value) {
    struct Node *currentPtr = rear;
    currentPtr->nextPtr = rear;

    // Set first to new node
    rear = currentPtr;

}
//Doesnt Works

void setValues(int works, int position) {

    struct Node *currentPtr = rear;
    //printf("identify %c  position %d\n",currentPtr->identify,currentPtr->position);
    currentPtr->works = works;
    currentPtr->position = position;
}

void removeFromFront() {

    struct Node *currentPtr = rear;
    currentPtr = currentPtr->nextPtr;
    rear = currentPtr;

}

void killList() {
    struct Node *currentPtr = rear;
    while (currentPtr->nextPtr != NULL) {
        rear = currentPtr;

        currentPtr = currentPtr->nextPtr;
    }


}

void removeFromBack() {

    struct Node *currentPtr = rear;
    struct Node * prePtr;
    prePtr = (struct Node *) malloc(sizeof (struct Node));
    while (currentPtr->nextPtr != NULL) {
        prePtr = currentPtr;
        currentPtr = currentPtr->nextPtr;

    }
    prePtr->nextPtr = NULL;

}

int display() {
    struct Node *var = rear;
    if (var != NULL) {

        while (var != NULL) {
            // printf("identify: %c ",var->identify);
            // printf("inData: %d ",var->inData);
            // printf("works: %d ",var->works);
            // printf("Old: %d \n",var->old);
            // printf("position: %d \n",var->position);
            //printf("Num %d\n",num );

            var = var->nextPtr;

        }
        printf("\n");
        return 1;
 
    } else
        //printf("\nQueue is Empty \n");
        return 0;
}
void bFit(int * sizes, char * identify, int theSize);
void wFit(int * sizes, char * identify, int theSize);
void nFit(int * sizes, char * identify, int theSize);
void fFit(int * sizes, char * identify, int theSize);
void memPrint(char * procA);
void addNext(char * procA, int numProc);
void rMem(char * procA, struct Node cNode);


