#include "myshell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h> // Directory entry
#include <errno.h> // Error number definitions
#include <ctype.h> // For isspace()

void change_directory(char *path)
{
  if (path == NULL)
  {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
      printf("%s\n", cwd);
    } else {
      perror("getcwd() error");
    }
  } else {
    if (chdir(path) != 0) {
      perror("myshell");
    }
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
