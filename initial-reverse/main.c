#include "dynamic_array.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void handle_error(const char *msg);

int main(int argc, char **argv)
{
    FILE *input = stdin;
    FILE *output = stdout;
    const char *outfile = NULL;

    if (argc == 2)
    {
        outfile = argv[1];
    }
    else if (argc == 3)
    {
        input = fopen(argv[1], "r");
        if (!input)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            return EXIT_FAILURE;
        }
        outfile = argv[2];
    }
    else if (argc > 3)
    {
        handle_error("usage: reverse <input> <output>\n");
    }

    if (outfile)
    {
        output = fopen(outfile, "w");
        if (!output)
        {
            fprintf(stderr, "reverse: cannot open file '%s'\n", outfile);
            if (input != stdin)
                fclose(input);
            return EXIT_FAILURE;
        }

        struct stat sb1, sb2;
        if (input != stdin && fstat(fileno(input), &sb1) != -1 && fstat(fileno(output), &sb2) != -1)
        {
            if (sb1.st_ino == sb2.st_ino)
            {
                handle_error("reverse: input and output file must differ\n");
            }
        }
    }

    dynamic_array_ts *dynamic_array = dynamic_array_new(100);
    if (!dynamic_array)
    {
        handle_error("malloc failed\n");
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read_len;

    while ((read_len = getline(&line, &len, input)) != -1)
    {
        char *line_copy = strdup(line);
        if (!line_copy)
        {
            handle_error("strdup failed\n");
        }
        dynamic_array_append(dynamic_array, line_copy);
    }

    free(line);
    if (input != stdin)
        fclose(input);

    while (dynamic_array->len)
    {
        char *popped = dynamic_array_pop(dynamic_array);
        if (popped)
        {
            fprintf(output, "%s", popped);
            free(popped);
        }
    }

    dynamic_array_destroy(dynamic_array);
    dynamic_array_free(&dynamic_array);
    if (output != stdout)
        fclose(output);

    return EXIT_SUCCESS;
}

static void handle_error(const char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}
