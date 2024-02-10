#include "myshell.h"

#define RESET "\x1b[0m"
#define ERROR "\x1b[31m"
#define PURP "\x1b[35m"
#define CYAN "\x1b[36m"


void execute_command(char *input);

int main(int argc, char *argv[])
{
    set_shell_environment_variable();

    if (argc > 1) {
        // Batch mode
        execute_batch_mode(argv[1]);
        return 0;
    }

    char input[1024]; // Buffer for user input
    while (1)
    {
    	getcwd(input, sizeof(input));
        printf(PURP "MyShell> " CYAN "%s> " RESET, input);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break; // Exit on EOF or error
        }
        execute_command(input); // Process the input
    }
    return 0;
}

void execute_command(char *input)
{
    char *token;
    char *delim = " \n";
    token = strtok(input, delim);

    if (token == NULL) return; // No input

    if (strcmp(token, "cd") == 0) {
        token = strtok(NULL, delim);
        change_directory(token);
    } else if (strcmp(token, "clr") == 0) {
        system("clear");
    } else if (strcmp(token, "dir") == 0) {
        token = strtok(NULL, delim);
        list_directory_contents(token); 
    } else if (strcmp(token, "environ") == 0) {
        list_environment_strings(); 
    } else if (strcmp(token, "echo") == 0) {
        echo_input(token + strlen(token) + 1); // Pass the rest of the input
    } else if (strcmp(token, "help") == 0) {
        system("more user_manual.txt"); // Assuming user_manual.txt exists
    } else if (strcmp(token, "pause") == 0) {
        pause_shell(); 
    } else if (strcmp(token, "quit") == 0) {
        exit(0);
    } else {
        execute_external_command(input);
    }
}



/*#include "myshell.h"

// Takes a single argument, input, which is a pointer to a character array (string). This function is responsible for parsing the input command and executing it accordingly.
void execute_command(char *input)
{
  char *token;
  char *delim = " \n";
  token = strtok (input, delim);
	//check if there is input
  if (token != NULL) 
  {
    if (strcmp(token, "cd") == 0) 
    {
      token = strtok(NULL, delim); // Get next part (directory path)
      change_directory(token);
    } else if (strcmp(token, "pwd") == 0)
    { system("pwd");
    } else {
      printf("Command not found");
    }
  }
}

int main()
{
  char input[1024]; // Buffer for user input
  while (1)
  {
    printf("MyShell> ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
      break; // Exit on EOF
    }
    execute_command(input); // Process the input
  }
  return 0;
}
*/
/*
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

*/
