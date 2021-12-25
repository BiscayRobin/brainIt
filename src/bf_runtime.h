#ifndef __BF_RUNTIME_H
#define __BF_RUNTIME_H

#include <stdlib.h>

#define BF_STDOUT_ERROR 2
#define BF_STDIN_ERROR 1
#define BF_SUCCESS 0

typedef struct
{
    char tape[30000];
    size_t head_idx;
} bf_runtime_t;

int bf_run(char *source, size_t source_length);

#endif // __BF_RUNTIME_H
