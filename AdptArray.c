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


// creating adt, takes three arguments and retruns NULL if fails 
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
        return;
    }

    for (int i = 0; i < adt->size; i++)
    {
        if (adt->addArr[i]) { // elements can be NULL
            adt->delete_func(adt->addArr[i]);
        }
    }

    free(adt->addArr);
    free(adt);
}

Result SetAdptArrayAt(PAdptArray adt, int i, PElement element) {
    if (!adt || !element)
    {
        return FAIL;
    }
    if (i < 0)
    {
        return FAIL;
    }
    
    if (i + 1 < adt->size) // there is such index in array
    {
        if (adt->addArr[i]) // not NULL, free current element
        {
            free(adt->addArr[i]);
        }
        adt->addArr[i] = adt->copy_func(element);
        return SUCCESS;
    }
    else { // array is too small, incrase its size 
        PElement* new_arr = (PElement)calloc(i + 1, sizeof(PElement));
        // copy all elements
        for (int i = 0; i < adt->size; i++)
        {
            if (adt->addArr[i]) // not NULL
            {
                new_arr[i] = adt->addArr[i];
            }
            else {
                new_arr[i] = NULL;
            }
        }
        free(adt->addArr);
        adt->addArr = new_arr;
        adt->addArr[i] = adt->copy_func(element);
        adt->size = i + 1;
        return SUCCESS;
    }
    
    
}

PElement GetAdptArrayAt(PAdptArray adt, int i) {

    if (!adt)
    {
        return NULL; 
    }
    if (adt->size < i || i < 0)
    {
        return NULL;
    }
    if (adt->addArr[i] == NULL)
    {
        return NULL;
    }

    return adt->copy_func(adt->addArr[i]);
    
}

int GetAdptArraySize(PAdptArray adt) {

    if (!adt)
    {
        return -1;
    }

    return adt ? adt->size : -1;   
}

void PrintDB(PAdptArray adt) {

    if (!adt)
    {
        return;
    }

    for (int i = 0; i < adt->size; i++)
    {
        if (adt->addArr[i])
        {
            adt->print_func(adt->addArr[i]);
        }
    }
}







