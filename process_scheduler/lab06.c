#include "task.h"
#include "sim.h"
#include <stdio.h>

int main(int argc, char **argv) {

  int n;
  scanf("%d", &n);

  unsigned int pid, priority, cycles;

  for (int i = 0; i < n; i++) {
    scanf("%d %d %d", &pid, &priority, &cycles);
    append_task(pid, priority, cycles);
  }

  printf("----initial tasks----\n");
  print_tasks();

  unsigned int index;
  scanf("%d %d %d %d", &index, &pid, &priority, &cycles);
  insert_task(index, pid, priority, cycles);
  printf("----insert task----\n");
  printf("insert task{%d:%d} at index %d with %d cycles\n", pid, priority, index, cycles);
  print_tasks();

  scanf("%d %d", &index, &pid);
  printf("----set task----\n");
  set_task(index, pid);
  printf("set task {pid:%d} to index %d\n", pid, index);
  print_tasks();

  scanf("%d", &index);
  task_struct *p = get_task(index);
  printf("----get task----\n");
  printf("task at index %d: pid=%d priority=%d remaining cycles=%d\n", index, p->pid, p->priority, p->remaining_cycles);

  schedule();
  printf("---schedule----\n");
  print_tasks();

  printf("----remove_task----\n");
  scanf("%d", &pid);
  printf("remove task pid=%d\n", pid);
  remove_task(pid);
  print_tasks();

  unsigned int pid_2;
  printf("----swap task----\n");
  scanf("%d %d", &pid, &pid_2);
  printf("swap task: pid=%d <-> pid=%d\n", pid, pid_2);
  swap(pid, pid_2);
  print_tasks();

  if (argc == 1) {
      printf("----clear all tasks----\n");
      clear();
      print_tasks();
  } else {
      printf("----dispatch tasks----\n");
      dispatcher(CYCLES_PER_TASK); 
  }


  return 0;

} 
