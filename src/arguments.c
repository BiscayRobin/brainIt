#include "arguments.h"

#include <stdio.h>
#include <stdlib.h>

int argument_parse(int argc, char **argv, args_t *args_result)
{
    char *prog_name = argv[0];

    if (argc != 2)
    {
        fprintf(stderr, "usage: ./%s source.bf", prog_name);
        return EXIT_FAILURE;
    }

    args_result->in_file = argv[1];
};
