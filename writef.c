/**
    * @file writef.c
    * @brief write to a file system time, pid and ppid
    * @details if the file exists, it will be appended to
    * @version 0.2
    * @date 06.11.2022
    * @author isaidsari
    * @bug no known bugs
    * @todo no todos
    * @warning no warnings
    * @note no notes
    * @see no references
    * @copyright no copyrigths
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s -f <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filename = argv[2];

    FILE *file = fopen(filename, "a");
    if(file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return EXIT_FAILURE;
    }
    
    size_t size = fprintf(file, "time: %ld, PID: %d, PPID: %d\n", time(NULL), getpid(), getppid());
    if (size < 0)
    {
        printf("Could not write to file %s\n", filename);
        return EXIT_FAILURE;
    }
    else
    {
        printf("Wrote %ld bytes to file %s\n", size, filename);
    }

    fclose(file);

    return EXIT_SUCCESS;
}