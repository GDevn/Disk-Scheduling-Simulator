/*
 * FILE:        util.h
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     To simply contain small utility functions which are used within larger,
 *              "complex" functions.
 */

#include <stdio.h>
#include <stdlib.h>

#include "util.h"

/* 
 * NAME:        getColCount
 * PURPOSE:     Used to help with file reading. To read beforehand, and return the
 *              number of columns in the file.
 * IMPORTS:     filename
 * EXPORTS:     cols
 */
int getColCount(char* fileName)
{
    FILE* f = fopen(fileName, "r");
    int cols = 0;
    int number, value;
    int done = 0;

    do
    {
        value = fscanf(f, "%d", &number);
        if(ferror(f))
        {
            perror("Error reading from file.\n");
            done = 1;
        }
        else if(value == -1)
        {
            done = 1;
        }
        else
        {
            cols++;
        }
    } while (!done);

    fclose(f);
    
    return cols;
}

/* 
 * NAME:        allocArray
 * PURPOSE:     To simply allocate memory to an array with given
 *              size.
 * IMPORTS:     array, size
 * EXPORTS:     void
 */
void allocArray(int** array, int size)
{
    *array = (int*)malloc((size) * sizeof(int));
}

/* 
 * NAME:        copyArray
 * PURPOSE:     To simply copy the contents of an array to another.
 * IMPORTS:     original, copy, size
 * EXPORTS:     void
 */
void copyArray(int* original, int* copy, int size)
{
    int i, counter = 0;

    for(i = 3; i < size; i++)
    {
        copy[counter] = original[i];
        counter++;
    }
}

/* 
 * NAME:        sortArray
 * PURPOSE:     To simply sort the contents of an array, from 
 *              lowest to largest.
 * IMPORTS:     array, size
 * EXPORTS:     void
 */
void sortArray(int* array, int size)
{
    int i, j, temp;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size-i-1; j++)
        {
            if(array[j] > array[j+1])
            {
                temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}

/* 
 * NAME:        getIndex
 * PURPOSE:     Used to get the index of the element which is closest
 *              to the initial location of the head.
 * IMPORTS:     array, currentPOS, size
 * EXPORTS:     index
 */
int getIndex(int* array, int currentPOS, int size)
{
    int i, prev, index = -1;

    prev = array[0];

    for(i = 0; i < size; i++)
    {
        if(currentPOS >= prev && currentPOS <= array[i])
        {
            index = i;
        }
        prev = array[i];
    }
    return index;
}

/* 
 * NAME:        isIncreasing
 * PURPOSE:     To simply return the boolean, if the head is initialy
 *              decreasing or increasing. I.e. boolean == 1 if it 
 *              is increasing.
 * IMPORTS:     currentPOS, previous
 * EXPORTS:     boolean
 */
int isIncreasing(int currentPOS, int previous)
{
    int boolean = 0;
    if(currentPOS > previous)
    {
        boolean = 1;
    }
    return boolean;
}

/* 
 * NAME:        calcSeekTime
 * PURPOSE:     To simply return the 'absolute' difference between
 *              two values. I.e. the seek time from one position
 *              to the other.
 * IMPORTS:     seekTime, value1, value2
 * EXPORTS:     void
 */
void calcSeekTime( int* seekTime, int value1, int value2)
{
    *seekTime = *seekTime + abs(value1 - value2);
}



/* 
 * NAME:        findMinMovement
 * PURPOSE:     To iterate through a sorted array and find the cylinder
 *              which requires the least amount of movement. As well,
 *              as update the location of the cylinder, which was
 *              passed in as an import, i.e. minIdx.
 * IMPORTS:     array, size, currentPOS, minIdx
 * EXPORTS:     currMinMovement
 */
int findMinMovement(int* array, int size, int currentPOS, int* minIdx)
{
    int i, diff, currMinMovement = 9999;

    for(i = 0; i < size; i++)
    {
        diff = abs(array[i] - currentPOS);
        if(currMinMovement > diff)
        {
            currMinMovement = diff;
            *minIdx = i;
        }
    }
    return currMinMovement;
}

/* 
 * NAME:        compare
 * PURPOSE:     To simply compare two strings and return if they are
 *              equal. I.e. equal == 1 if both strings are the same.
 * IMPORTS:     string1, string2
 * EXPORTS:     equal
 */
int compare(char* string1, char* string2)
{
    int equal = 1;
    while(*string1 && *string2)
    {
        if(*string1 != *string2)
        {
            equal = 0;
        }
        string1++;
        string2++;
    }
    return equal;
}