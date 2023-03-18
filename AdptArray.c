#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>


// defining the ADT
typedef struct AdptArray_
{
    PElement* addArr;
    COPY_FUNC copy_func;
    DEL_FUNC delete_func;
    PRINT_FUNC print_func;
    int size;
}AdptArray_;


// creating adt, takes three arguments and retruns NULL id fails 
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func ,PRINT_FUNC print_func) {

    PAdptArray adt = (PAdptArray)malloc(sizeof(AdptArray_));
    if (!adt)
    {
        return NULL;
    }

    adt->addArr = (PElement*)malloc(sizeof(PElement));
    adt->copy_func = copy_func;
    adt->delete_func = del_func;
    adt->print_func = print_func;
    adt->size= 0;

    return adt;
}

// free adt alongside all its elements
void DeleteAdptArray(PAdptArray adt) {

    if (!adt)
    {
        return NULL;
    }

    PElement current; 
    for (int i = 0; i < adt->size; i++)
    {
        if (adt->addArr[i]) { // elements can be NULL
            adt->delete_func(adt->addArr[i]);
        }
    }

    free(adt->addArr);
    free(adt);
}

Result SetAdptArrayAt(PAdptArray adt, int index, PElement element) {

}

PElement GetAdptArrayAt(PAdptArray adt, int i) {

    if (!adt)
    {
        return NULL; 
    }
    if (adt->size < i)
    {
        return NULL;
    }
    if (!adt->addArr[i])
    {
        return FAIL;
    }

    return adt->copy_func(adt->addArr[i]);
    
}

int GetAdptArraySize(PAdptArray adt) {

    if (!adt)
    {
        return -1;
    }

    return adt->size;   
}

void PrintDB(PAdptArray adt) {

    if (!adt)
    {
        return NULL;
    }

    for (int i = 0; i < adt->size; i++)
    {
        if (adt->addArr[i])
        {
            adt->print_func(adt->addArr[i]);
        }
    }
}







