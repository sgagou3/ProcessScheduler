#include "task.h"

#include <stddef.h>

#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#define TASK_OP_PASS 0
#define TASK_OP_ERROR 1
#define NOT_FOUND 0
#define DEBUG 0

task_struct * head = NULL;
task_struct * tail = NULL;

void clear() {
  while (head != NULL) {
    task_struct * temp = head -> next;
    free(head);
    head = temp;
  }
  head = NULL;
  tail = NULL;
} 

unsigned int size() {
  if (head == NULL) return 0;
  unsigned int size = 1;
  task_struct * temp = head -> next;
  while (temp != NULL) {
    temp = temp -> next;
    size++;
  }
  return size;
} 
unsigned int append_task(unsigned int pid, unsigned int priority, int cycles) {
  if (exists(pid) != NULL || cycles <= 0) return TASK_OP_ERROR;

  task_struct * new_tail = malloc(sizeof(task_struct));

  new_tail -> pid = pid;
  new_tail -> priority = priority;
  new_tail -> remaining_cycles = cycles;
  new_tail -> next = NULL;

  if (size() == 0) {
    head = new_tail;
    tail = new_tail;
    return TASK_OP_PASS;
  }

  tail -> next = new_tail;
  tail = new_tail;

  return TASK_OP_PASS;
} 
unsigned int insert_task(unsigned int index, unsigned int pid, unsigned int priority, int cycles) {
  if (index < 0 || index > size()) {
    return TASK_OP_ERROR;
  }

  if (exists(pid) != NULL || cycles <= 0) return TASK_OP_ERROR;

  task_struct * added = malloc(sizeof(task_struct));
  added -> pid = pid;
  added -> priority = priority;
  added -> remaining_cycles = cycles;

  if (index == 0) {
    added -> next = head;
    head = added;
    if (size() == 0) {
      tail = added;
    }
  } else if (index == size()) {
    tail -> next = added;
    added -> next = NULL;
    tail = added;
  } else {
    task_struct * temp = get_task(index - 1);
    added -> next = temp -> next;
    temp -> next = added;
  }

  return TASK_OP_PASS;
}

unsigned int set_task(unsigned int index, unsigned int pid) {
  if (index < 0 || index >= size()) return TASK_OP_ERROR;
  if (exists(pid) == NULL) return TASK_OP_ERROR;
  task_struct * temp = exists(pid);
  if (get_task(index) -> pid == temp -> pid) return TASK_OP_ERROR;
  remove_task(temp -> pid);
  insert_task(index, temp -> pid, temp -> priority, temp -> remaining_cycles);
  return TASK_OP_PASS;
} 

task_struct * remove_task(unsigned int pid) {
  if (size() == 0) {
    return NULL;
  }
  task_struct * curr = head;
  if (exists(pid) == NULL) return NULL;
  if (head -> pid == pid) {
    head = head -> next;
    return curr;
  }
  for (int i = 0; i < size() - 1; i++) {
    if (curr -> next -> pid == pid) {
      task_struct * temp = curr -> next;
      if (curr -> next -> pid == tail -> pid) {
        tail = curr;
      }
      curr -> next = curr -> next -> next;
      return temp;
    }
    curr = curr -> next;
  }
  return NULL;
} 

task_struct * exists(unsigned int pid) {
  task_struct * temp = head;
  while (temp != NULL) {
    if (temp -> pid == pid) return temp;
    temp = temp -> next;
  }
  return NULL;
} 

task_struct * get_task(unsigned int index) {
  if (index < 0 || index >= size()) return NULL;
  unsigned int idx = 0;
  task_struct * temp = head;
  while (temp != NULL) {
    if (idx == index) return temp;
    idx++;
    temp = temp -> next;
  }
  return NULL; 
} 

unsigned int swap(unsigned int pid_1, unsigned int pid_2) {
  task_struct * first = exists(pid_1);
  task_struct * sec = exists(pid_2);

  if (first == NULL || sec == NULL || pid_1 == pid_2 || size() == 1) {
    return TASK_OP_ERROR;
  }

  task_struct * fake_node = malloc(sizeof(task_struct));
  fake_node -> pid = first -> pid;
  fake_node -> priority = first -> priority;
  fake_node -> remaining_cycles = first -> remaining_cycles;

  first -> pid = sec -> pid;
  first -> priority = sec -> priority;
  first -> remaining_cycles = sec -> remaining_cycles;

  sec -> pid = fake_node -> pid;
  sec -> priority = fake_node -> priority;
  sec -> remaining_cycles = fake_node -> remaining_cycles;

  free(fake_node);

  return TASK_OP_PASS;
}

void schedule() {
  if (size() == 0 || size() == 1) return;
  for (int i = (int) floor((size() - 2) / 2); i >= 0; i--) {
    int k = i;
    while (2 * k + 2 <= size()) {
      int j = 2 * k + 1;
      if (j + 1 < size()) {
        float j1_fl = (float) get_task(j + 1) -> priority / (float) get_task(j + 1) -> remaining_cycles;
        float j_fl = (float) get_task(j) -> priority / (float) get_task(j) -> remaining_cycles;
        if (compare_floats(j_fl, j1_fl) == 0 && get_task(j + 1) -> priority < get_task(j) -> priority) {
          j++;
        } else if (compare_floats(j_fl, j1_fl) == -1) {
          j++;
        }
      }
      float k_fl = (float) get_task(k) -> priority / (float) get_task(k) -> remaining_cycles;
      float j_fl = (float) get_task(j) -> priority / (float) get_task(j) -> remaining_cycles;
      if (compare_floats(k_fl, j_fl) == 1) {
        break;
      } else if (get_task(k) -> priority <= get_task(j) -> priority && compare_floats(k_fl, j_fl) == 0) {
        break;
      } else {
        swap(get_task(k) -> pid, get_task(j) -> pid);
        k = j;
      }
    }
  }
}


void print_tasks() {
  task_struct * p_task = head;

  if (p_task == NULL) {
    printf("[ empty ]\n");
  } else {
    printf("(%d)[", size());

    while (p_task != NULL) {
      printf(" %d:%d:%d:%.2f", p_task -> pid, p_task -> priority, p_task -> remaining_cycles, (float) p_task -> priority / (float) p_task -> remaining_cycles);
      p_task = p_task -> next;
    }

    printf(" ]\n");
  }

} 

int compare_floats(float a, float b) {
  const float epsilon = 0.0001;
  return fabs(a - b) < epsilon ? 0 : a < b ? 1 : -1;
} 