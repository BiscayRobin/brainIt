#ifndef __ARGUMENTS_H
#define __ARGUMENTS_H

typedef struct
{
    char *in_file;
} args_t;

int argument_parse(int argc, char **argv, args_t *args_result);

#endif // __ARGUMENTS_H