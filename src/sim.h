#include <math.h>

#define CYCLES_PER_TASK 5

void dispatcher(unsigned int cycles_per_task);

void run(task_struct* task, unsigned int num_cycles);
