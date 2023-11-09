/*
 * FILE:        util.h
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     Header file for utility functions.
 */

#ifndef UTIL_H
#define UTIL_H

int getColCount(char*);

void allocArray(int**, int);
void copyArray(int*, int*, int);
void sortArray(int*, int);

int getIndex(int*, int, int);
int isIncreasing(int, int);
void calcSeekTime(int*, int, int);
int findMinMovement(int*, int, int, int*);

int compare(char*, char*);

#endif