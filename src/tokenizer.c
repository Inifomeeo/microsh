#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "tokenizer.h"

// Split input into tokens separated by a space
char **tokenize_input(char *input, char *delim)
{
    int buf_size = 10;
    int index = 0;
    char **tokens = malloc(buf_size * sizeof(char *));
    if (tokens == NULL) {
        perror("malloc: char **tokens");
        exit(1);
    }
    char *token;

    token = strtok(input, delim);
    while (token != NULL) {
        tokens[index] = token;
        index++;

        if (index >= buf_size) {
            buf_size += buf_size;
            tokens = realloc(tokens, buf_size * sizeof(char *));
            if (tokens == NULL) {
                perror("realloc: tokens");
                exit(1);
            }
        }

        token = strtok(NULL, delim);
    }

    tokens[index] = NULL;
    return tokens;
}