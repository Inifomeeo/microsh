#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"

int main()
{
    char *input;
    char **command;
    pid_t pid;
    int buf_size = 128;
    int stat_loc;
    
    while (1)
    {
        // Print prompt
        printf("$ ");
        fflush(stdout);

        input = malloc(buf_size * sizeof(char));
        if (input == NULL) {
            perror("malloc");
            exit(1);
        }

        // Wait for user input
        fgets(input, buf_size, stdin);
        input[strcspn(input, "\r\n")] = 0;

        command = tokenize_input(input);
        if (!command[0]) {
            free(input);
            free(command);
            continue;
        }

        pid = fork();
        if (pid == 0) {
            if (execvp(command[0], command) < 0) {
                perror("execvp");
                exit(1);
            }
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        } else {
            waitpid(pid, &stat_loc, WUNTRACED);
        }

        free(input);
        free(command);
    }
    
    return 0;
}