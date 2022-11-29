/**
 * @file    writef.c
 * @brief   write to a file system pid, ppid and time
 * @details if the file exists, it will be appended to
 * @version 0.4
 * @date    06.11.2022-28.11.2022
 * @author  isaidsari
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// function prototype
char *get_date(void);

int main(int argc, char *argv[])
{
    // usage : writef -f <filename>

    // check if the number of arguments is correct
    if (argc != 3)
    {
        printf("usage: %s -f <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // check if the first argument is -f
    if (strcmp(argv[1], "-f") != 0)
    {
        printf("usage: %s '-f' <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // take file name as argument
    char *filename = argv[2];

#ifdef DEBUG
    printf("debug: filename = %s\n", filename);
#endif

    // check if file name argument is empty
    if (strlen(filename) == 0)
    {
        printf("usage: %s -f '<filename>'\n", argv[0]);
        return EXIT_FAILURE;
    }

    // open the file in append mode
    // if the file does not exist, it will be created
    // if the file exists, it will be appended to
    FILE *file = fopen(filename, "a");

    // check if the file was opened successfully
    if (file == NULL)
    {
        printf("could not open file %s\n", filename);
        return EXIT_FAILURE;
    }

    char *date = get_date();

    // write the pid, ppid and date to the file
    int size = fprintf(file, "pid: %d, ppid: %d, time: %lu, date: %s\n", getpid(), getppid(), time(NULL), date);

    // check if the write was successful
    if (size < 0)
    {
        printf("could not write to file %s\n", filename);
        return EXIT_FAILURE;
    }
    else
    {
        printf("wrote %d bytes to file %s\n", size, filename);
    }

    // free the date string
    free(date);

    // close the file
    fclose(file);

    return EXIT_SUCCESS;
}

char *get_date()
{
    // convert time to date and clock string
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    // "dd/mm/yyyy hh:mm:ss"
    char *date = (char *)malloc(20 * sizeof(char));
    // format tm struct to date string
    sprintf(date, "%d/%d/%d %d:%d:%d",
            tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);

    return date;
}
