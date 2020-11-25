/* Objective: to create an array of pointers to handle processes */

#define MAXPROC_LIMIT 512

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

/* 
 * This is just a placeholder for a more advanced process struct. Linux's
 * struct has like 10 million different attributes, this can be changed later. 
 */

typedef struct proc {
	int32_t pid;
	int32_t gid;
	int32_t uid;
} proc;

/* Here we will create an array of pointers to each process_struct for easier handling. */

proc *procptr[MAXPROC_LIMIT];

/* This code to zero out the array should be run after every reboot before ANY processes are loaded. */

void zero_processes(void) {
	int i;

	for (i = 0; i < MAXPROC_LIMIT; i++) {
		procptr[i] = NULL;
	}
}

/* 
 * AddProcess() takes a pointer *st to a struct as it's only argument, and copies the data st* points
 * to into another struct pointer which hold's malloc()'s return value. This is done for security and
 * efficiency purposes for the sake of memory management. It is expected of DelProcess() to call free().
 */
 
int add_process(proc *st) {
	int i;
	proc *ptr = NULL;

	if (st == NULL) {
		return -1;
	}

	for (i = 0; i < MAXPROC_LIMIT; i++) {
		if (procptr[i] == NULL) {

			ptr = malloc(sizeof(proc));
			*ptr = *st;
			procptr[i] = ptr;
			return 0;

		}
	}

/* If our array is full return -2. We put our return code here because this is a non-void function. */

	free(ptr);
	return -2;
}

/* 
 * DelProcess() simply takes one argument of type int pid, scans the existing process array for a 
 * corresponding value and free()'s the location. Return 0 on Success, -1 on Failure.
 */

int del_process(int pid) {
	int i;

	for (i = 0; i < MAXPROC_LIMIT; i++) {
		if (procptr[i] != NULL && procptr[i]->pid == pid) {
			free(procptr[i]);
			procptr[i] = NULL;
			return 0;
		}
	}
	return -1;
}

/* get_process_info() just returns location of existing process. Self evident. Returns NULL pointer on fail. */

proc *get_process_info(int pid) {
	int i;

	for(i = 0; i < MAXPROC_LIMIT; i++) {
		if (procptr[i] != NULL && procptr[i]->pid == pid) {
			return procptr[i];
		}
	}
	return NULL;
}