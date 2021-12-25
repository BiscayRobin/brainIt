#include <stdio.h>

#include "bf_runtime.h"

int bf_run(char *source, size_t source_length)
{
    bf_runtime_t bf_runtime = {0};
    size_t source_idx = 0;

    while (source_idx < source_length)
    {
        char curr_op = source[source_idx];
        size_t loop_depth = 0;
        switch (curr_op)
        {
        case '+':
            bf_runtime.tape[bf_runtime.head_idx]++;
            break;
        case '-':
            bf_runtime.tape[bf_runtime.head_idx]--;
            break;
        case '>':
            bf_runtime.head_idx++;
            break;
        case '<':
            bf_runtime.head_idx--;
            break;
        case '.':
            if (putchar(bf_runtime.tape[bf_runtime.head_idx]) == EOF)
            {
                return BF_STDOUT_ERROR;
            }
            break;
        case ',':
            bf_runtime.tape[bf_runtime.head_idx] = getchar();
            if (ferror(stdin))
            {
                return BF_STDIN_ERROR;
            }
            break;
        case '[':
            if (source[source_idx + 1] == '-' && source[source_idx + 2] == ']')
            {
                bf_runtime.tape[bf_runtime.head_idx] = 0;
                source_idx += 1;
            }
            if (!bf_runtime.tape[bf_runtime.head_idx])
            {
                source_idx++;
                while (source[source_idx] != ']' || loop_depth != 0)
                {
                    if (source[source_idx] == '[')
                        loop_depth++;
                    else if (source[source_idx] == ']')
                        loop_depth--;
                    source_idx++;
                }
            }
            break;
        case ']':
            if (bf_runtime.tape[bf_runtime.head_idx])
            {
                source_idx--;
                while (source[source_idx] != '[' || loop_depth != 0)
                {
                    if (source[source_idx] == ']')
                        loop_depth++;
                    else if (source[source_idx] == '[')
                        loop_depth--;
                    source_idx--;
                }
            }
            break;
        default:
            // ignore all unknown operations
            break;
        }
        source_idx++;
    }
    return BF_SUCCESS;
}
