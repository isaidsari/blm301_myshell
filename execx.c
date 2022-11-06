/**
* @file execx.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    // usage : execx -t <times> <program> <arguments>

    // check if the number of arguments is correct
    if (argc < 4)
    {
        printf("Usage: %s -t <times> <program> <arguments>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // check if the first argument is -t
    if (strcmp(argv[1], "-t") != 0)
    {
        printf("Usage: %s -t <times> <program> <arguments>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // convert the second argument to an integer
    int times = atoi(argv[2]);

    // check if the second argument is a positive integer
    if (times <= 0)
    {
        printf("Usage: %s -t <times> <program> <arguments>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // set child's arguments
    int c_argc = argc - 3;
    char *c_argv[c_argc];
    memcpy(c_args, argv + 3, sizeof(char *) * c_argc);

    // run the program x times
    for (int i = 0; i < times; i++)
    {
        // fork a new process
        pid_t pid = fork();

        // check if the fork failed
        if (pid < 0)
        {
            printf("Fork failed");
            return EXIT_FAILURE;
        }

        // check if we are in the child process
        if (pid == 0)
        {
            // run the program,
            execvp(c_argv[0], c_argv);

            // if execvp returns, it failed
            printf("Exec failed");
            return EXIT_FAILURE;
        }

        // wait for the child process to finish
        wait(NULL);

        // print the number of the current iteration
        printf("Iteration %d", i + 1);

        // check if this is the last iteration
        if (i == times - 1)
        {
            printf("program %s finished", args[0]);
        }
    }

    return EXIT_SUCCESS;
}
