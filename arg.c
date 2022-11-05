// simple argument parsing

#include "arg.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// parse arguments
// returns 0 on success, 1 on failure

int arg_parse(int argc, char **argv, arg_t *arg) {
    int i;
    int j;
    
    // set defaults
    arg->input = NULL;
    arg->output = NULL;
    arg->verbose = 0;
    arg->help = 0;

    // parse arguments
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                arg->input = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "error: missing input file name after -i option (try -h for help)");
                return 1;
            }


        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                arg->output = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "error: missing output file name after -o option (try -h for help)");
                return 1;
            }

        } else if (strcmp(argv[i], "-v") == 0) {
            arg->verbose = 1;

        } else if (strcmp(argv[i], "-h") == 0) {
            arg->help = 1;

        } else {
            fprintf(stderr, "error: unknown option %s (try -h for help)", argv[i]);
            return 1;
        }
    }

    // check for required arguments

    if (arg->input == NULL) {
        fprintf(stderr, "error: missing input file name (try -h for help)");
        return 1;
    }

    
    if (arg->output == NULL) {
        fprintf(stderr, "error: missing output file name (try -h for help)");
        return 1;
    }

    return 0;
}

// print help message

void arg_print_help() {
    printf("usage: arg [options] [arguments] ... ");
    printf("options: ");
    printf("-i input file name ");
    printf("-o output file name ");
    printf("-v verbose ");
    printf("-h help ");
}

// print version message

void arg_print_version() {
    printf("arg version 1.0");
}

// print usage message

void arg_print_usage() {
    printf("usage: arg [options] [arguments] ... ");
}

// print error message

void arg_print_error() {
    printf("error: unknown option (try -h for help)");
}
