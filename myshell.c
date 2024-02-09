#include "myshell.h"
#include <dirent.h> // Directory entry
#include <errno.h> // Error number definitions
#include <ctype.h> // For isspace()

void execute_command(char *input);
void set_shell_environment_variable();
void execute_external_command(char *input);
void execute_batch_mode(char *filename);

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
        printf("MyShell> ");
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
        list_directory_contents(token); // This function needs to be implemented
    } else if (strcmp(token, "environ") == 0) {
        list_environment_strings(); // This function needs to be implemented
    } else if (strcmp(token, "echo") == 0) {
        echo_input(token + strlen(token) + 1); // Pass the rest of the input
    } else if (strcmp(token, "help") == 0) {
        system("more user_manual.txt"); // Assuming user_manual.txt exists
    } else if (strcmp(token, "pause") == 0) {
        pause_shell(); // This function needs to be implemented
    } else if (strcmp(token, "quit") == 0) {
        exit(0);
    } else {
        execute_external_command(input);
    }
}

void execute_external_command(char *input)
{
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        char *envp[] = { NULL }; // Setup environment if necessary
        char *argv[] = { "/bin/sh", "-c", input, NULL };
        if (execve("/bin/sh", argv, envp) == -1) {
            perror("myshell");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        // Parent process
        wait(NULL); // Wait for the child process to finish
    } else {
        // Failed to fork
        perror("myshell");
    }
}

void execute_batch_mode(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("myshell");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        execute_command(line);
    }

    fclose(file);
}

void set_shell_environment_variable()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char shell_env[1024];
        sprintf(shell_env, "SHELL=%s/myshell", cwd);
        putenv(shell_env);
    } else {
        perror("getcwd() error");
    }
}

void list_directory_contents(char *path)
{
    DIR *d;
    struct dirent *dir;
    if (path == NULL) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            path = cwd;
        } else {
            perror("getcwd() error");
            return;
        }
    }
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    } else {
        perror("opendir() error");
    }
}

extern char **environ; // Environment variables

void list_environment_strings()
{
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);
    }
}

void pause_shell()
{
    printf("Press 'Enter' to continue...\n");
    while (getchar() != '\n');
    // Clear the input buffer in case of additional characters before the newline
    while (getchar() != '\n' && !feof(stdin) && !ferror(stdin));
}

void echo_input(char *input)
{
    int in_space = 1; // Start assuming we're leading with spaces
    while (*input) {
        if (isspace((unsigned char)*input)) {
            // If we encounter a space and it's the first one after a word
            if (!in_space) {
                putchar(' '); // Print a single space
                in_space = 1; // and mark that we're now in a space
            }
        } else {
            // If it's not a space, print the character
            putchar(*input);
            in_space = 0; // and mark that we're not in a space
        }
        input++;
    }
    putchar('\n'); // Print a newline at the end
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
