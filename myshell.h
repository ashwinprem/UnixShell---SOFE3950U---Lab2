#ifndef MYSHELL_H
#define MYSHELL_H
#include <stdio.h> // Standard I/O functions
#include <stdlib.h> // Standard library for functions like malloc
#include <string.h> // String handling functions
#include <unistd.h> // Provides access to the POSIX operating system API
void list_directory_contents(char *path);
void list_environment_strings();
void pause_shell();
void change_directory(char *path); // declaration of 'cd' function (cd function prototype)
void echo_input(char *input); // Declare echo_input function
#endif
