#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>

// defins the ADT
typedef struct AdptArray_
{
    PElement* adpArr;
    COPY_FUNC copy_func;
    DEL_FUNC delete_func;
    PRINT_FUNC print_func;
    int size;
}AdptArray_;


/**
 * creats adaptArr, takes three arguments and retruns NULL if fails 
 * @param copy_func copy function
 * @param del_func delete function
 * @param print_func print function
 * @return initilized ADT
*/
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func ,PRINT_FUNC print_func) {

    PAdptArray adaptArr = (PAdptArray)malloc(sizeof(AdptArray_));
    if (!adaptArr)
    {
        return NULL;
    }

    adaptArr->adpArr = (PElement*)malloc(sizeof(PElement)); 
    adaptArr->copy_func = copy_func;
    adaptArr->delete_func = del_func;
    adaptArr->print_func = print_func;
    adaptArr->size= 0;

    return adaptArr;
}

/**
 * deletes adaptArr alongside its elements
 * @param adaptArr adaptArr to delete
*/
void DeleteAdptArray(PAdptArray adaptArr) {

    if (!adaptArr)
    {
        return;
    }

    for (int i = 0; i < adaptArr->size; i++)
    {
        if (adaptArr->adpArr[i]) { // elements can be NULL
            adaptArr->delete_func(adaptArr->adpArr[i]);
        }
    }

    free(adaptArr->adpArr);
    free(adaptArr);
}

/**
 * puts element in adaptArr in a given index
 * @param adaptArr adaptArr to set 
 * @param i index to set
 * @param element element to put in the adaptArr
 * @return 1 or 0 if the set operation succeded or faild
*/
Result SetAdptArrayAt(PAdptArray adaptArr, int i, PElement element) {
    if (!adaptArr || !element)
    {
        return FAIL;
    }
    if (i < 0)
    {
        return FAIL;
    }
    
    if (i + 1 < adaptArr->size) // there is such index in array
    {
        if (adaptArr->adpArr[i]) // not NULL, free current element
        {
            free(adaptArr->adpArr[i]);
        }
        adaptArr->adpArr[i] = adaptArr->copy_func(element);
        return SUCCESS;
    }
    else { // array is too small, incrase its size 
        PElement* new_arr = (PElement)calloc(i + 1, sizeof(PElement));
        // copy all elements
        for (int i = 0; i < adaptArr->size; i++)
        {
            if (adaptArr->adpArr[i]) // not NULL
            {
                new_arr[i] = adaptArr->adpArr[i];
            }
            else {
                new_arr[i] = NULL;
            }
        }
        free(adaptArr->adpArr);
        adaptArr->adpArr = new_arr;
        adaptArr->adpArr[i] = adaptArr->copy_func(element);
        adaptArr->size = i + 1;
        return SUCCESS;
    }
    
    
}

/**
 * gets element from the adaptArr from given index
 * @param adaptArr adaptArr to get from
 * @param i which index to get
 * @return element in the given index, NULL if not exist
*/
PElement GetAdptArrayAt(PAdptArray adaptArr, int i) {

    if (!adaptArr)
    {
        return NULL; 
    }
    if (adaptArr->size < i || i < 0)
    {
        return NULL;
    }
    if (adaptArr->adpArr[i] == NULL)
    {
        return NULL;
    }

    return adaptArr->copy_func(adaptArr->adpArr[i]);
    
}

/**
 * gets adaptArr aize
 * @param adaptArr adaptArr to get its size
 * @return size of adaptArr
*/
int GetAdptArraySize(PAdptArray adaptArr) {

    if (!adaptArr)
    {
        return -1;
    }

    return adaptArr ? adaptArr->size : -1;   
}

/**
 * prints all array elements
 * @param adaptArr array to print
*/
void PrintDB(PAdptArray adaptArr) {

    if (!adaptArr)
    {
        return;
    }

    for (int i = 0; i < adaptArr->size; i++)
    {
        if (adaptArr->adpArr[i])
        {
            adaptArr->print_func(adaptArr->adpArr[i]);
        }
    }
}







