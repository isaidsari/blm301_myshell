// linux shell myshell implementation

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(/*int argc, char *argv[]*/)
{
    while(1)
    {
        // print the prompt
        printf("myshell>> ");
        // read the command
        char command[100];
        fgets(command, 100, stdin);
        // remove the newline character
        command[strlen(command) - 1] = '\0';
        // split the command into tokens
        char *tokens[100];
        char *token = strtok(command, " ");
        int i = 0;
        while(token != NULL)
        {
            tokens[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        tokens[i] = NULL;
        // execute the command
        if(strcmp(tokens[0], "exit") == 0)
        {
            // exit the shell
            exit(0);
        }
        else if (strcmp(tokens[0], "bash") == 0)
        {
            // call bash
            pid_t pid = fork();
            if(pid == 0)
            {
                // child process
                // execute the command
                execvp("/bin/bash", tokens);
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
        else
        {
            // fork a child process
            pid_t pid = fork();
            if(pid == 0)
            {
                // print tokens
                /*
                for(int i = 0; tokens[i] != NULL; i++)
                {
                    printf("%s\n", tokens[i]);
                }
                */


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
