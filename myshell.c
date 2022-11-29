/**
 * @file    myshell.c
 * @brief   linux shell myshell implementation
 * @version 0.4
 * @date    05.11.2022-28.11.2022
 * @author  isaidsari
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

    // allocate memory for the buffer
    // char command[BUFFER_SIZE];
    char *command = (char *)malloc(BUFFER_SIZE * sizeof(char));
    // max token count is buffer_size / 2
    // because tokens are separated by space
    // char *tokens[BUFFER_SIZE / 2];
    char **tokens = (char **)malloc((BUFFER_SIZE / 2) * sizeof(char *));

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

#ifdef DEBUG
        printf("debug: command [%lu] %s\n", strlen(command), command);
#endif

        // check if buffer is empty
        if (strlen(command) == 0)
        {
            printf("myshell: no command provided\n");
            // skip the rest of the loop
            // ask for new command
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
            // tokens[i] = token;

            if (strcmp(token, "writef") == 0)
            {tokens[i] = "./writef";}
            else if (strcmp(token, "execx") == 0)
            {tokens[i] = "./execx";}
            else
            {tokens[i] = token;}
            // else if (strcmp(token, "cat") == 0)
            // {tokens[i] = "/bin/cat";} ...

            token = strtok(NULL, " ");
            i++;
        }
        // add NULL to the end of the tokens
        tokens[i] = NULL;

        // execute the command
        // check if the command is 'exit' then break
        if (strcmp(tokens[0], "exit") == 0)
        {
            // exit the shell
            // exit(0);
            // return EXIT_SUCCESS;
            break;
        }
        // if command is 'help' then display help
        else if (strcmp(tokens[0], "help") == 0)
        {
            // print help message
            printf("myshell supports this commands:\n");
            printf("exit                                   ? exit the shell\n");
            printf("help                                   ? print this help message\n");
            printf("execx -t <number of iterations> <args> ? executes args t times\n");
            printf("writef -f <filename>                   ? writes the time, pid and ppid to file\n");
        }
        else
        {
            // fork a child process
            pid_t pid = fork();
            if (pid == 0)
            {
                // child process
                // execute the command
                if (execvp(tokens[0], tokens) == -1)
                {
                    printf("myshell: an error occured while executing command '%s'\n", tokens[0]);
                    return EXIT_FAILURE;
                }
                // execvp(tokens[0], tokens);
                //  if execvp returns, there is an error
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
    // free memory resources
    free(command);
    free(tokens);
    return EXIT_SUCCESS;
}
