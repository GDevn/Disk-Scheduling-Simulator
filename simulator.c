/*
 * FILE:        simulator.c
 * AUTHOR:      George Devean Sinining
 * -----
 * PURPOSE:     Provides the functions which simulate the various disk scheduling
 *              algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "simulator.h"
#include "util.h"
#include "scheduler.h"
#include "fileIO.h"

int* buffer1 = NULL;
int buffer2 = 0;

/* 'Boolean' variables to let the child threads know when to contiue executing. */
int completedInput = 0;
int quit = 0;

/* Used to store all the values(seektime) calculated by the child threads. */
int* ret = NULL;

/* Conditional Variables. */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t inputCond = PTHREAD_COND_INITIALIZER;

/*
 * NAME:        selectScheduler
 * PURPOSE:     To simply select the disk scheduling algorithm that is associated with the 
                option imported, calculate the seek time and return the result.
 * IMPORTS:     option, array, size
 * EXPORTS:     seekTime
 */
int selectScheduler(int option, int* array, int size)
{
    int seekTime = 0;
    if(option == 0)
    {
        seekTime = fcfs(array, size);
    }
    else if(option == 1)
    {
        seekTime = sstf(array, size);
    }
    else if(option == 2)
    {
        seekTime = scan(array, size);
    }
    else if(option == 3)
    {
        seekTime = cScan(array, size);
    }
    else if(option == 4)
    {
        seekTime = look(array, size);
    }
    else if(option == 5)
    {
        seekTime = cLook(array, size);
    }
    return seekTime;
}

/*
 * NAME:        child
 * PURPOSE:     The function which the child threads performs and calculate
                the seek time.
 * IMPORTS:     arg
 * EXPORTS:     NULL
 */
void* child(void* arg)
{
    int option;

    /* Thread blocks, and waits to get input from parent thread. */
    pthread_mutex_lock(&mutex);
    option = *(int*)arg;
    
    /* Child waits until the parent thread completes getting input and signals. */
    while(completedInput == 0)
    {
        pthread_cond_wait(&inputCond, &mutex);
    };
    
    /* If the parent completes reading input and signals child, and the input was not */
    /* 'QUIT', calculate seekTime using buffer1. */
    if(completedInput == 1 && !quit)
    {
        buffer2 = selectScheduler(option, buffer1, 11);

        /* Store the seek time into the return array, which contains all the */
        /* seek time calculations. */
        ret[option] = buffer2;
    }

    free(arg);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

/*
 * NAME:        parent
 * PURPOSE:     The function which the parent thread performs.
 * IMPORTS:     arg
 * EXPORTS:     input
 */
void* parent(void* arg)
{
    int cols, i;
    int loopCond = 0;
    int validInput = 0;
    char* input;

    input = (char*)malloc(10 * sizeof(char));

    pthread_mutex_lock(&mutex);

    /* Loop to get input from user. */
    do
    {
        printf("Enter the filename or 'QUIT' to exit: ");
        scanf("%s", input);
        printf("%s\n", input);
    
        if(compare(input, "QUIT"))
        {
            loopCond = 1;
        }
        else if(validFile(input) == 0)
        {
            printf("Invalid filename try again.\n");
        }
        else
        {
            validInput = 1;
            loopCond = 1;
        }
    } while(loopCond == 0);

    system("clear");

    if(validInput == 1)
    {
        cols = getColCount(input);
        buffer1 = (int*)malloc(cols * sizeof(int));

        readFile(input, buffer1, cols);
    }
    else
    {
        quit = 1;
    }

    /* Set the boolean which the child threads use to exit wait to true */
    /* Indicating that the read was successful. */
    completedInput = 1;

    /* Signal child threads to continue*/
    for(i = 0; i < 6; i++)
    {
        pthread_cond_signal(&inputCond);
    }

    pthread_mutex_unlock(&mutex);

    return input;
}

/*
 * NAME:        performSimulator
 * PURPOSE:     Function that 'links' all the previous functions above, which is
                called by main.
 * IMPORTS:     void
 * EXPORTS:     void
 */
void performSimulator()
{
    int i;
    int* a;
    pthread_t threads[7];
    char* filename = NULL;

    char* schdNames[6] = {"FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK"};

    ret = (int*)malloc(6 * sizeof(int));

    /* Create threads */
    for(i = 0; i < 7; i++)
    {
        if(i == 6)
        {
            if(pthread_create(&threads[i], NULL, &parent, NULL) != 0)
            {
                perror("Failed to create thread\n");
            }
        }
        else
        {
            a = malloc(sizeof(int));
            *a = i;
            if(pthread_create(&threads[i], NULL, &child, a) != 0)
            {
                perror("Failed to create thread\n");
            }
        }
    }

    /* Join threads and get their results */
    for(i = 0; i < 7; i++)
    {
        if(i == 6)
        {
            if(pthread_join(threads[i], (void*)&filename) != 0)
            {
                perror("Failed to create thread\n");
            }
        }
        else
        {
            if(pthread_join(threads[i], NULL) != 0)
            {
                perror("Failed to create thread\n");
            }
        }
        
        if(quit)
        {
            printf("Thread %ld has terminated\n", threads[i]);
        }
    }

    /* If the user did not exit print results. */
    if(!quit)
    {
        free(buffer1);
        for(i = 0; i < 6; i++)
        {
            if(i == 0)
            {
                printf("Disk Scheduling Simulation:\n\nFor %s\n", filename);
            }
            printf("%s: %d\n", schdNames[i], ret[i]);
        }
    }
    free(ret);
    free(filename);
}