all: myshell

myshell: myshell.c utility.c
	gcc -o myshell myshell.c utility.c -I.
