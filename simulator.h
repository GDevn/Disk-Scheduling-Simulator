/*
 * FILE:        simulator.h
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     Header file for simulator functions  
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

void performSimulator(void);

int selectScheduler(int, int*, int);

void* child(void*);
void* parent(void*);

#endif