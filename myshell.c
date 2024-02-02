#include "myshell.h"

void execute_command(char *input)
{
  char *token;
  char *delim = " \n";
  token = strtok (input, delim);

  if (token != NULL) 
  {
    if (strcmp(token, "cd") == 0) 
    {
      token = strtok(NULL, delim); // Get next part (directory path)
      change_directory(token);
    } else {
      system("pwd");
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
