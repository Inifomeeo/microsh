#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    char *input;
    
    while (1)
    {
        // Print prompt
        printf("$ ");
        fflush(stdout);

        input = malloc(100 * sizeof(char));
        if (input = NULL) {
            perror("malloc");
            exit(1);
        }

        // Wait for user input
        fgets(input, 100, stdin);
        input[strcspn(input, "\r\n")] = 0;

        free(input);
    }
    
    return 0;
}