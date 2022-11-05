// this file runs program x times with fork() and exec() system calls
// compile with: gcc -o execx execx.c
// run with: ./execx x

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // check for the correct number of arguments
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./execx x");
        return 1;
    }
    // convert the argument to an integer
    int x = atoi(argv[1]);
    // fork x child processes
    for(int i = 0; i < x; i++)
    {
        pid_t pid = fork();
        if(pid == 0)
        {
            // child process
            // execute the command
            char *args[] = {"./hello", NULL};
            execvp(args[0], args);
            // if execvp returns, there is an error
            perror("execvp");
            exit(1);
        }
        else
        {
            // parent process
            // wait for the child process to finish
            wait(NULL);
        }
    }
    return 0;

}
