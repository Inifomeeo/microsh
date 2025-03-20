#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "tokenizer.h"

char **tokenize_input(char *input) {
    char **tokens = malloc(10 * sizeof(char*));
    if (tokens == NULL) {
        perror("malloc");
        exit(1);
    }
    char *token;
    int index = 0;

    token = strtok(input, " ");
    while (token != NULL) {
        tokens[index] = token;
        index++;

        token = strtok(NULL, " ");
    }

    tokens[index] = NULL;
    return tokens;
}