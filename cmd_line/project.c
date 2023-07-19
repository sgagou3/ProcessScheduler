#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {

    int cmd_cnt = 0;

    char shell_cmd[101] = "\0";        

    command_t command;

    while ( 1 ) {

        printf("(%d)$ ", cmd_cnt++);                  
        fgets( shell_cmd, 100, stdin );
        shell_cmd[strcspn(shell_cmd, "\n")] = 0;      
        parse( shell_cmd, &command );

        // Execute command
        if ( command.argc > 0 ) {
            if ( execute( &command ) == ERROR ) {
                fprintf(stderr, "%s command failed\n", shell_cmd );
            }
        }

        cleanup(&command);
    }

    return 0;

} 
