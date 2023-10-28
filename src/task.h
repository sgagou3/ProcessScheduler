#include <math.h>

#ifndef _TASK_H_
#define _TASK_H_
typedef struct task_struct {
    unsigned int priority;		
    unsigned int pid;		
    int remaining_cycles;	
    struct task_struct* next;	
} task_struct;
#endif

void clear();

unsigned int size();

unsigned int append_task(unsigned int pid, unsigned int priority, int cycles);

unsigned int insert_task(unsigned int index, unsigned int pid, unsigned int priority, int cycles);

unsigned int set_task(unsigned int index, unsigned int pid);

task_struct* remove_task(unsigned int pid);

task_struct* exists(unsigned int pid);

task_struct* get_task(unsigned int index);

unsigned int swap(unsigned int pid_1, unsigned int pid_2);

void schedule();

void print_tasks();

int compare_floats(float a, float b);
