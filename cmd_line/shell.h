#define SUCCESS 0
#define ERROR -1
#define EXIT 1

#define TRUE 1
#define FALSE 0

#define DEBUG 0
#define MAX_ARG_LEN 100

typedef struct {

    int argc;    // total number of arguments
    char** argv; // argument values (must malloc)

} command_t;

void alloc_mem_for_command(command_t* p_cmd, int argc);

void cleanup(command_t* p_cmd);

void parse(char* line, command_t* p_cmd);

int find_fullpath(command_t* p_cmd);

int execute(command_t* p_cmd);

int is_builtin(command_t* p_cmd);

int do_builtin(command_t* p_cmd);
