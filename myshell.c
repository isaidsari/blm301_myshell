/**
 * @file myshell.c
 * @brief linux shell myshell implementation
 * @version 0.4
 * @date 05.11.2022-28.11.2022
 * @author isaidsari
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
#ifdef DEBUG
    printf("\033[1;31m");
    printf("debug: debug mode is on\n");
    printf("\033[0m");
#endif

    char command[BUFFER_SIZE];
    // max token count is buffer_size / 2
    // because tokens are separated by space
    char *tokens[BUFFER_SIZE / 2];

    while (true)
    {
        // print the prompt
        printf("myshell>> ");
        // read the command
        if (fgets(command, BUFFER_SIZE, stdin) == NULL)
        {
            printf("myshell: error occured while reading command");
            return EXIT_FAILURE;
        }

        // remove the newline character from the end of the command
        command[strlen(command) - 1] = '\0';

        // trim spaces from the beginning of the command
        char *trimmed_command = command;
        while (*trimmed_command == ' ')
        {
            trimmed_command++;
        }
        strcpy(command, trimmed_command);

        // check if buffer is empty
        if (strlen(command) == 0)
        {
            printf("myshell: no command provided\n");
            continue;
        }

        // split the command into tokens
        char *token = strtok(command, " ");
        int i = 0;
        while (token != NULL)
        {

#ifdef DEBUG
            printf("debug: token [%d] = '%s'\n", i, token);
#endif
            tokens[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        // add NULL to the end of the tokens
        tokens[i] = NULL;

        if (strcmp(tokens[0], "writef") == 0)
        {
            tokens[0] = "./writef";
        }
        if (strcmp(tokens[0], "execx") == 0)
        {
            tokens[0] = "./execx";
        }

        // execute the command
        if (strcmp(tokens[0], "exit") == 0)
        {
            // exit the shell
            // exit(0);
            return EXIT_SUCCESS;
        }
        else if (strcmp(tokens[0], "help") == 0)
        {
            // print help message
            printf("myshell supports this commands:\n");
            printf("exit                                   ? exit the shell\n");
            printf("help                                   ? print this help message\n");
            printf("execx -t <number of iterations> <args> ? executes args t times\n");
            printf("writef -f <filename>                   ? writes the time, pid and ppid to file\n");
        }
        else if (strcmp(tokens[0], "bash") == 0)
        {
            // call bash
            pid_t pid = fork();
            if (pid == 0)
            {
                // child process
                // execute the command
                char *bash_argv[] = {"/bin/bash", NULL};
                execvp("/bin/bash", bash_argv);
                // if execvp returns, there is an error
                perror("execvp");
                return EXIT_FAILURE;
            }
            else
            {
                // parent process
                // wait for the child process to finish
                wait(NULL);
            }
        }
        else
        {
            // fork a child process
            pid_t pid = fork();
            if (pid == 0)
            {
                // child process
                // execute the command
                execvp(tokens[0], tokens);
                // if execvp returns, there is an error
                perror("execvp");
                return EXIT_FAILURE;
            }
            else
            {
                // parent process
                // wait for the child process to finish
                wait(NULL);
            }
        }
    }
}
