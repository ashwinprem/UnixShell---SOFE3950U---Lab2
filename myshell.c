#include "myshell.h"
void execute_command(char *input) {
    char *token;
    char *delim = " \n";
    token = strtok(input, delim);

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

