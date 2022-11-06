#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *value;
} Arg;

typedef struct {
    Arg *args;
    int len;
} ArgList;
