/*
 * FILE:        fileIO.c
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     Handles all the File I/O operations, such as reading and writing
 *              to files.
 */

#include <stdio.h>
#include <stdlib.h>

#include "fileIO.h"

/*
 * NAME:        readFile
 * PURPOSE:     To read a file and store the contents into the array that was
                passed in.
 * IMPORTS:     filename, array, size
 * EXPORTS:     void
 */
void readFile(char* filename, int* array, int size)
{
    int i, value;

    FILE* f = fopen(filename, "r");

    for(i = 0; i < size; i++)
    {
        fscanf(f, "%d", &value);
        array[i] = value;
    }

    fclose(f);
}

/*
 * NAME:        validFile
 * PURPOSE:     To take in the filename, read and see if it can be opened.
 * IMPORTS:     filename
 * EXPORTS:     valid
 */
int validFile(char* filename)
{
    int valid = 1;
    
    FILE* f = fopen(filename, "r");

    if(f == NULL)
    {
        valid = 0;
    }
    else
    {
        fclose(f);
    }
    return valid;
}