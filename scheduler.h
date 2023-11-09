/*
 * FILE:        scheduler.h
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     Header file for scheduler functions  
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

int fcfs(int*, int);
int sstf(int*, int);

int scan(int*, int);
int cScan(int*, int);

int look();
int cLook(int*, int);

#endif