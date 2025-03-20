#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "tokenizer.h"

int main() {
    char *input;
    char **command;
    
    while (1)
    {
        // Print prompt
        printf("$ ");
        fflush(stdout);

        input = malloc(128 * sizeof(char));
        if (input == NULL) {
            perror("malloc");
            exit(1);
        }

        // Wait for user input
        fgets(input, 128, stdin);
        input[strcspn(input, "\r\n")] = 0;

        command = tokenize_input(input);
        if (!command[0]) {
            free(input);
            free(command);
            continue;
        }

        free(input);
        free(command);
    }
    
    return 0;
}