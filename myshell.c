#include "myshell.h"

// Takes a single argument, input, which is a pointer to a character array (string). This function is responsible for parsing the input command and executing it accordingly.
void execute_command(char *input) {
    char *token;
    char *delim = " \n";
    token = strtok(input, delim);

    // First token checks to see if it's a recognized command.
    if (token != NULL) {
        // Attempts to get the next token (directory path). Calls change_directory to change the current working directory.
        if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, delim);
            change_directory(token);

        // Prints error otherwise.
        } else {
            printf("Command not recognized.\n");
        }
    }
}
int main() {
    char input[1024]; // Buffer for user input

    // Processes input until EOF.
    while (1) {
        printf("MyShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exits on EOF
        }
        execute_command(input); // Process the input
    }

    return 0;
}

