#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bf_runtime.h"
#include "arguments.h"
#include "utils.h"

int main(int argc, char **argv)
{
    int error_code = 0;

    args_t arguments = {0};
    argument_parse(argc, argv, &arguments);

    char *source_code;

    size_t source_length = file_to_buffer(arguments.in_file, &source_code);

    if ((error_code = bf_run(source_code, source_length)))
    {
        char *error_message;
        switch (error_code)
        {
        case BF_STDIN_ERROR:
            error_message = "could not read from stdin";
            break;
        case BF_STDOUT_ERROR:
            error_message = "could not write to stdout";
            break;
        default:
            error_message = "unknown error";
            break;
        }
        fprintf(stderr, "Error(%d): %s", error_code, error_message);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
