#ifndef __ARGUMENTS_H
#define __ARGUMENTS_H

#include <stdbool.h>

typedef struct
{
    char *in_file;
    char *out_file;
    bool isCompiled;
} args_t;

int argument_parse(int argc, char **argv, args_t *args_result);

#endif // __ARGUMENTS_H
