/**
    * @file writef.c
    * @brief Write to a file using fprintf
    * @details Write to a file using fprintf
    * @version 0.1
    * @date 2023
*/

/**
* @file Dosya adı
* @description Programınızın açıklaması ne yaptığına dair.
* @assignment Kaçıncı ödev olduğu
* @date Kodu oluşturduğunuz Tarih
* @author yazar adı ve mail adresi
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char *argv[])
{
    // file name taken from parent process arguments
    char *filename = argv[1];
    // open the file
    FILE *file = fopen(filename, "w");
    if(file == NULL)
    {
        fprintf(stderr, "Could not open file %s", filename);
        return 1;
    }
    // write the system clock
    fprintf(file, "System clock: %ld", time(NULL));
    // write the pid
    fprintf(file, "Process ID: %d", getpid());
    // write the ppid
    fprintf(file, "Parent process ID: %d", getppid());
    // close the file
    fclose(file);

    return 0;
}