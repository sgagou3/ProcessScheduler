#include <ctype.h>

#include <fcntl.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <unistd.h>

#include "shell.h"

const char * PATH_SEPARATOR = ":";

const char * BUILT_IN_COMMANDS[] = {
  "cd",
  "exit",
  NULL
};

void alloc_mem_for_command(command_t * p_cmd, int argc) {
  p_cmd -> argc = argc;
  p_cmd -> argv = malloc(sizeof(char * ) * (argc + 1));
  for (int i = 0; i < argc + 1; i++) {
    p_cmd -> argv[i] = malloc(sizeof(char) * MAX_ARG_LEN);
  }
  p_cmd -> argv[argc] = NULL;
}

void cleanup(command_t * p_cmd) {
  for (int i = 0; i < p_cmd -> argc + 1; i++) {
    free(p_cmd -> argv[i]);
    p_cmd -> argv[i] = NULL;
  }
  free(p_cmd -> argv);
  p_cmd -> argv = NULL;
}

void parse(char * line, command_t * p_cmd) {
  int argc_ct = 0;
  int idx = 0;
  int j = 0;
  int args = 0;

  while (line[idx] != '\0') {
    if (line[idx] != ' ') {
      argc_ct++;
    }
    idx++;
  }
  idx = 0;

  alloc_mem_for_command(p_cmd, argc_ct);
  while (line[idx] != '\0') {
    if (line[idx] == ' ') {
      while (line[idx + 1] == ' ') {
        idx++;
      }
      if (line[idx + 1] != '\0') {
        p_cmd -> argv[args][j] = '\0';
        args++;
        j = 0;

      }
    } else {
      p_cmd -> argv[args][j] = line[idx];
      j++;

    }
    idx++;
  }
  p_cmd -> argv[args + 1] = NULL;
  p_cmd -> argv[args][j] = '\0';
} 

int find_fullpath(command_t * p_cmd) {
  char * env = getenv("PATH");
  //this serves no use, 
  //just need it for strtok_r since strtok can't move between strings/pointers
  void * fake_ptr;
  char fib[MAX_ARG_LEN];
  strncpy(fib, env, strlen(env));
  //set null terminator
  fib[strlen(env)] = '\0';
  char * cmd = p_cmd -> argv[0];
  char * snippet;
  snippet = strtok_r(fib, PATH_SEPARATOR, & fake_ptr);

  while (snippet) {
    char curr[MAX_ARG_LEN];
    //make sure to copy over the path that's being searched
    strcpy(curr, snippet);
    strcat(curr, "/");
    strcat(curr, cmd);
    struct stat buffer;
    //if the path exists, update the path in p_cmd and return true
    if (stat(curr, & buffer) == 0 && (S_IFREG & buffer.st_mode)) {
      strcpy(cmd, curr);
      return TRUE;
    }
    snippet = strtok_r(NULL, PATH_SEPARATOR, & fake_ptr);
  }
  return ERROR;
} 

int execute(command_t * p_cmd) {
  //base case
  if (p_cmd -> argc == 0) return SUCCESS;
  int status = SUCCESS;
  int child_process_status;
  int wait_status;
  pid_t child_pid;
  if (is_builtin(p_cmd)) {
    //if we already have the command, just execute it
    do_builtin(p_cmd);
  } else {
    if (find_fullpath(p_cmd) != ERROR) {
      //fork the pid
      child_pid = fork();
      //any time we get a negative value from a syscall, it is an error
      if (child_pid == 0) {
        if (execv(p_cmd -> argv[0], p_cmd -> argv) == -1) return ERROR;
        _exit(0);
      } else if (child_pid < 0) {
        return ERROR;
      }
      wait( & wait_status);
    } else {
      printf("Command '%s' not found!\n", p_cmd -> argv[0]);
      return SUCCESS;
    }
  }
  return status;

} 

int is_builtin(command_t * p_cmd) {

  int cnt = 0;

  while (BUILT_IN_COMMANDS[cnt] != NULL) {

    if (strcmp(p_cmd -> argv[0], BUILT_IN_COMMANDS[cnt]) == 0) {
      return TRUE;
    }

    cnt++;
  }

  return FALSE;

} 
int do_builtin(command_t * p_cmd) {
  // If the command was 'cd', then change directories
  // otherwise, tell the program to EXIT

  struct stat buff;
  int status = SUCCESS;

  // exit
  if (strcmp(p_cmd -> argv[0], "exit") == 0) {
    exit(status);
  }

  // cd
  if (p_cmd -> argc == 1) {
    // -----------------------
    // cd with no arg
    // -----------------------
    // change working directory to that
    // specified in HOME environmental
    // variable

    status = chdir(getenv("HOME"));
  } else if ((status = stat(p_cmd -> argv[1], & buff)) == 0 && (S_IFDIR & buff.st_mode)) {
    // -----------------------
    // cd with one arg
    // -----------------------
    // only perform this operation if the requested
    // folder exists

    status = chdir(p_cmd -> argv[1]);
  }

  return status;

} 