#include "utils.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

size_t file_to_buffer(char *file_path, char **buffer_addr)
{
    FILE *file_stream = fopen(file_path, "rb");

    if (!file_stream)
    {
        fprintf(stderr, "%s: %s\n", file_path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    size_t source_length;

    fseek(file_stream, 0, SEEK_END);
    source_length = ftell(file_stream);
    fseek(file_stream, 0, SEEK_SET);

    if (!(*buffer_addr = malloc(source_length)))
    {
        fclose(file_stream);
        fprintf(stderr, "Fatal: Could not allocate %zu bytes\n", source_length);
        exit(EXIT_FAILURE);
    }

    fread(*buffer_addr, 1, source_length, file_stream);

    int error_code;

    if ((error_code = ferror(file_stream)))
    {
        fclose(file_stream);
        fprintf(stderr, "%s: %s\n", file_path, strerror(error_code));
        exit(EXIT_FAILURE);
    }

    fclose(file_stream);

    return source_length;
}