#include "arguments.h"

#include <stdio.h>
#include <stdlib.h>
#include <argp.h>

error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    args_t *arguments = state->input;
    switch (key)
    {
    case 'o':
        arguments->out_file = arg;
        break;
    case 'c':
        arguments->isCompiled = true;
        break;
    case ARGP_KEY_ARG:
        if (state->arg_num >= 1)
            argp_usage(state);
        arguments->in_file = arg;
        break;
    case ARGP_KEY_END:
        if (state->arg_num < 1)
            argp_usage(state);
        break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

const char *argp_program_version =
    "brainIt v0.1";

static char doc[] =
    "brainIt -- An intepreter for brainfuck.";

static char args_doc[] = "INPUT";

static struct argp_option options[] =
    {
        {.name = "output",
         .key = 'o',
         .doc = "Print program outputs to a file.",
         .group = 0},
        {.name = "compilation-target",
         .key = 'c',
         .doc = "supported architectures are: x86_64",
         .group = 1},
        {0}};

static struct argp argp = {options, parse_opt, args_doc, doc, NULL, NULL, NULL};

int argument_parse(int argc, char **argv, args_t *args_result)
{
    return argp_parse(&argp, argc, argv, 0, 0, args_result);
}
