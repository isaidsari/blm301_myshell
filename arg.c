#include "arg.h"

ArgList *parse_args(int argc, char *argv[])
{
    ArgList *arg_list = malloc(sizeof(ArgList));
    arg_list->args = malloc(sizeof(Arg) * argc);
    arg_list->len = 0;

    for (int i = 0; i < argc; i++) {
        char *arg = argv[i];
        if (arg[0] == '-') {
            arg_list->args[arg_list->len].name = arg;
            arg_list->args[arg_list->len].value = NULL;
            arg_list->len++;
        } else {
            if (arg_list->len > 0) {
                arg_list->args[arg_list->len - 1].value = arg;
            }
        }
    }

    return arg_list;
}

Arg *get_arg(ArgList *arg_list, char *name)
{
    for (int i = 0; i < arg_list->len; i++) {
        Arg *arg = &arg_list->args[i];
        if (strcmp(arg->name, name) == 0) {
            return arg;
        }
    }
    return NULL;
}

void free_args(ArgList *arg_list)
{
    free(arg_list->args);
    free(arg_list);
}
