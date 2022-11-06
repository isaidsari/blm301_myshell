/**
    * @file writef.c
    * @brief write to a file system time, pid and ppid
    * @details if the file exists, it will be appended to
    * @version 0.3
    * @date 06.11.2022
    * @author isaidsari
    * @bug no known bugs
    * @warning no known warnings
    * @todo no known todos
    * @note no notes
    * @see no references
    * @copyright no copyrigths
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int main(int argc, char *argv[])
{
    // usage : writef -f <filename>

    // check if the number of arguments is correct
    if (argc != 3)
    {
        printf("Usage: %s -f <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // check if the first argument is -f
    if (strcmp(argv[1], "-f") != 0)
    {
        printf("Usage: %s -f <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // open the file in append mode
    // if the file does not exist, it will be created
    // if the file exists, it will be appended to
    char *filename = argv[2];
    FILE *file = fopen(filename, "a");

    // check if the file was opened successfully
    if(file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return EXIT_FAILURE;
    }
    
    // write the time, pid and ppid to the file
    int size = fprintf(file, "time: %ld, PID: %d, PPID: %d\n", time(NULL), getpid(), getppid());
    if(size < 0)
    {
        printf("Could not write to file %s\n", filename);
        return EXIT_FAILURE;
    }
    else
    {
        printf("Wrote %d bytes to file %s\n", size, filename);
    }

    // close the file
    fclose(file);

    return EXIT_SUCCESS;
}
