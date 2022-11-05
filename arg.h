// arg parsing header file

typedef struct {
    char *input;
    char *output;
    int verbose;
    int help;
} arg_t;

// parse arguments
// returns 0 on success, 1 on failure

int arg_parse(int argc, char **argv, arg_t *arg);

// print help message

void arg_print_help();

// print version message

void arg_print_version();

// print usage message

void arg_print_usage();

// print error message
