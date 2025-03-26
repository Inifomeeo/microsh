#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "tokenizer.h"

typedef struct {
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    if (input_buffer == NULL) {
        perror("malloc: InputBuffer *input_buffer");
        exit(1);
    }

    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
  
    return input_buffer;
}

void free_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

void read_line(InputBuffer *input_buffer)
{
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0) {
        free_input_buffer(input_buffer);
        perror("getline");
        exit(1);
    }
  
    // Remove trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

int main()
{
    char *home;
    char **command;
    pid_t pid;
    int exit_status;
    int stat_loc;
    InputBuffer* input_buffer;
    
    while (1) {
        // Print prompt
        printf("$ ");
        fflush(stdout);

        // Wait for user input
        input_buffer = new_input_buffer();
        read_line(input_buffer);

        command = tokenize_input(input_buffer->buffer, " ");
        if (!command[0]) {
            free_input_buffer(input_buffer);
            free(command);
            continue;
        }

        // The exit builtin
        if (strcmp(command[0], "exit") == 0) {
            exit_status = (command[1] != NULL) ? atoi(command[1]) : 0;
            free_input_buffer(input_buffer);
            free(command);
            exit(exit_status);
        }

        // The cd builtin
        if (strcmp(command[0], "cd") == 0) {
            if (command[1] == NULL) {
                fprintf(stderr, "cd: Missing argument\n");
            } else if (chdir(command[1]) < 0) {
                if (strcmp(command[1], "~") == 0) {
                    home = getenv("HOME");
                    chdir(home);
                } else {
                    fprintf(stderr, "cd: %s: No such file or directory\n", command[1]);
                }
            }

            continue;
        }

        pid = fork();
        if (pid == 0) {
            if (execvp(command[0], command) < 0) {
                perror("execvp: command not found");
                exit(1);
            }
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        } else {
            waitpid(pid, &stat_loc, WUNTRACED);
        }

        free_input_buffer(input_buffer);
        free(command);
    }
    
    return 0;
}