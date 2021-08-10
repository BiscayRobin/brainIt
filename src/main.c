#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "bf_runtime.h"

int main(int argc, char **argv)
{

    char *prog_name = argv[0];

    int error_code = 0;

    if (argc != 2)
    {
        fprintf(stderr, "usage: ./%s source.bf", prog_name);
        return EXIT_FAILURE;
    }

    char *source_path = argv[1];
    char *source_code;
    size_t source_length;

    FILE *file_stream = fopen(source_path, "rb");

    if (!file_stream)
    {
        fprintf(stderr, "%s: %s\n", source_path, strerror(errno));
        return EXIT_FAILURE;
    }

    fseek(file_stream, 0, SEEK_END);
    source_length = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    if (!(source_code = malloc(source_length)))
    {
        fprintf(stderr, "Fatal: Could not allocate %zu bytes\n", source_length);
        return EXIT_FAILURE;
    }

    fread(source_code, 1, source_length, file_stream);

    if ((error_code = ferror(file_stream)))
    {
        fprintf(stderr, "%s: %s\n", source_path, strerror(error_code));
        return EXIT_FAILURE;
    }

    fclose(file_stream);

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
        }
        fprintf(stderr, "Error(%d): %s", error_code, error_message);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
