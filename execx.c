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
    // usage : execx -t <times> <program> <args>

    // check if the number of arguments is correct
    if (argc < 4)
    {
        printf("Usage: %s -t <times> <program> <args>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // check if the first argument is -t
    if (strcmp(argv[1], "-t") != 0)
    {
        printf("Usage: %s -t <times> <program> <args>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // convert the second argument to an integer
    int times = atoi(argv[2]);

    // check if the second argument is a positive integer
    if (times <= 0)
    {
        printf("Usage: %s -t <times> <program> <args>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // set child's arguments
    int c_argc = argc - 3;
    char *c_argv[c_argc];
    memcpy(c_argv, argv + 3, sizeof(char *) * c_argc);
    // add NULL to the end of the arguments
    c_argv[c_argc] = NULL;

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
            #ifdef DEBUG
            // print the child's arguments
            printf("Child's arguments: ");
            for (int j = 0; j < c_argc; j++)
            {
                printf("%s ", c_argv[j]);
            }
            printf("\n");
            #endif

            // run the program
            execvp(c_argv[0], c_argv);

            // if execvp returns, it failed
            printf("Exec failed");
            return EXIT_FAILURE;
        }
        else
        {
            // wait for the child process to finish
            wait(NULL);

            #ifdef DEBUG
            // print the number of the current iteration
            printf("Iteration %d\n", i + 1);
            #endif

            // check if this is the last iteration
            if (i == times - 1)
            {
                printf("program %s finished\n", c_argv[0]);
            }
        }
    }
    return EXIT_SUCCESS;
}
