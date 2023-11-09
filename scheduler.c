/*
 * FILE:        scheduler.c
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     Provides the functions which implement the six
 *              disk scheduling algorithms.
 */

#include <stdio.h>
#include <stdlib.h>

#include "scheduler.h"
#include "util.h"

/*
 * NAME:        fcfs
 * PURPOSE:     To perform the 'First Come First Serve' disk scheuling
 *              algorithm
 * IMPORTS:     array, size
 * EXPORTS:     seekTime
 */
int fcfs(int* array, int size)
{
    int i, seekTime = 0, currentPOS = array[1];

    for(i = 3; i < size; i++)
    {
        calcSeekTime(&seekTime, array[i], currentPOS);
        currentPOS = array[i];
    }

    return seekTime;
}

/*
 * NAME:        sstf
 * PURPOSE:     To perform the 'Shortest Seek Time First' disk scheuling
 *              algorithm
 * IMPORTS:     array, size
 * EXPORTS:     seekTime
 */
int sstf(int* array, int size)
{
    int seekTime = 0, currentPOS = array[1];
    int* copy = NULL;

    /* Variables below needed to keep track of values during seek. */
    int count=0, minDiffIdx;

    allocArray(&copy, size-3);
    copyArray(array, copy, size);

    /* Only iterate for the length of the array, which contains the cylinder numbers. */
    while(count < size - 3)
    {
        seekTime = seekTime + findMinMovement(copy, size-3, currentPOS, &minDiffIdx);
        currentPOS = copy[minDiffIdx];

        /* Fill in index with a large number so that we don't seek for it again. */
        copy[minDiffIdx] = array[0] + 999;

        count++;
    }
    free(copy);
    return seekTime;
}

/*
 * NAME:        scan
 * PURPOSE:     To perform the 'Scan'' disk scheuling algorithm
 * IMPORTS:     array, size
 * EXPORTS:     seekTime
 */
int scan(int* array, int size)
{
    int i, index;
    int seekTime = 0;
    int* copy = NULL;

    int currentPOS = array[1], previousPOS = array[2], cylinders = array[0];

    allocArray(&copy, size-3);

    copyArray(array, copy, size);

    sortArray(copy, size-3);

    index = getIndex(copy, currentPOS, size-3);

    if(isIncreasing(currentPOS, previousPOS))
    {
        for(i = index; i < size-3; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }

        /* Get seek time for reaching end of disk. */
        calcSeekTime(&seekTime, cylinders, copy[i-1]-1);
        /* Update position. */
        currentPOS = cylinders - 1;
        for(i = index-1; i >= 0; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    else
    {
        for(i = index-1; i >= 0; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
        /* Get seek time for reaching end of disk. */
        seekTime = seekTime + abs(copy[i+1]);
        /* Update position. */
        currentPOS = 0;
        for(i = index; i < size-3; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    free(copy);
    return seekTime;
}

/*
 * NAME:        cScan
 * PURPOSE:     To perform the 'C-Scan' disk scheuling algorithm
 * IMPORTS:     array, size
 * EXPORTS:     seekTime
 */
int cScan(int* array, int size)
{
    int i, index;
    int seekTime = 0;
    int* copy = NULL;

    int currentPOS = array[1], previousPOS = array[2], cylinders = array[0];

    allocArray(&copy, size-3);

    copyArray(array, copy, size);

    sortArray(copy, size-3);

    index = getIndex(copy, currentPOS, size-3);

    if(isIncreasing(currentPOS, previousPOS))
    {
        for(i = index; i < size-3; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
        
        /* Get seek time for reaching end of disk. */
        calcSeekTime(&seekTime, cylinders-1, copy[i-1]);
        /* Add seek time for reaching to the other side of disk. */
        seekTime = seekTime + abs(cylinders-1);
        /* Update position. */
        currentPOS=0;

        for(i = 0; i < index; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    else
    {
        for(i = index-1; i >= 0; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
            
        }

        seekTime = seekTime + abs(copy[i+1]);
        seekTime = seekTime + abs(cylinders-1);
        currentPOS = cylinders - 1;

        for(i = size-3-1; i >= index; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
            
        }
    }
    free(copy);
    return seekTime;
}

/*
 * NAME:        look
 * PURPOSE:     To perform the 'look' disk scheuling algorithm
 * IMPORTS:     array, size
 * EXPORTS:     seekTime
 */
int look(int* array, int size)
{
    int seekTime = 0;
    int index, i;

    int* copy = NULL;

    int currentPOS = array[1], previousPOS = array[2];

    allocArray(&copy, size-3);
    copyArray(array, copy, size);
    sortArray(copy, size-3);

    index = getIndex(copy, currentPOS, size-3);

    if(isIncreasing(currentPOS, previousPOS))
    {
        for(i = index; i < size-3; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }

        for(i = index-1; i >= 0; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    else
    {
        for(i = index-1; i >= 0; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }

        for(i = index; i < size-3; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    free(copy);
    return seekTime;
}

/*
 * NAME:        cLook
 * PURPOSE:     To perform the 'C-Look' disk scheuling algorithm
 * IMPORTS:     array, size
 * EXPORTS:     seekTime
 */
int cLook(int* array, int size)
{
    int seekTime = 0;
    int index, i;

    int* copy = NULL;

    int currentPOS = array[1], previousPOS = array[2];

    allocArray(&copy, size-3);
    copyArray(array, copy, size);
    sortArray(copy, size-3);

    index = getIndex(copy, currentPOS, size-3);

    if(isIncreasing(currentPOS, previousPOS))
    {
        for(i = index; i < size-3; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }

        for(i = 0; i < index; i++)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    else
    {
        for(i = index-1; i>=0; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }

        for(i = size-3-1; i >= index; i--)
        {
            calcSeekTime(&seekTime, copy[i], currentPOS);
            currentPOS = copy[i];
        }
    }
    free(copy);
    return seekTime;
}