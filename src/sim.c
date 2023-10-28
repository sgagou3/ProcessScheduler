#include "task.h"

#include "sim.h"

#include <stdio.h>

#include <stdlib.h>

void dispatcher(unsigned int cycles_per_task) {
  while (size() > 0) {
    schedule();
    task_struct * removed = remove_task(get_task(0) -> pid);
    run(removed, cycles_per_task);
    if (removed -> remaining_cycles > 0) {
      append_task(removed -> pid, removed -> priority, removed -> remaining_cycles);
    }
  }
}

void run(task_struct * task, unsigned int num_cycles) {
  task -> remaining_cycles -= num_cycles;
  printf("Task %d run for %d cycle(s).\n", task -> pid, num_cycles);
  if (task -> remaining_cycles <= 0) {
    printf("Task %d Completed.\n", task -> pid);
  }
} 
