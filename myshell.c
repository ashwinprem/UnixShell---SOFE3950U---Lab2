#include "myshell.h"

//Takes a single argument, input, which is a pointer to a character array (string). This function is responsible for parsing the input command and executing it accordingly.
void execute_command(char *input) {
    char *token;
    char *delim = " \n";
    token = strtok(input, delim);

    /* The first token is checked to see if it's a recognized command, then it attempts to get the next token, (directory path), 
    and calls change_directory to change the current working directory. Prints error otherwise. */
    if (token != NULL) {
        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, delim);
            change_directory(token);
        } else {
            printf("Command not recognized.\n");
        }
    }
}
int main() {
    char input[1024];

    while (1) {
        printf("MyShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        execute_command(input);
    }

    return 0;
}

