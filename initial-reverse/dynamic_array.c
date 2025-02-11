#include "dynamic_array.h"

static dynamic_array_ts *dynamic_array_init(dynamic_array_ts *dynamic_array, size_t size)
{
    if (dynamic_array)
    {
        if (size)
        {
            dynamic_array->size = size;
            dynamic_array->len = 0;
            dynamic_array->items = malloc(size * sizeof(char *));
            if (!dynamic_array->items)
                dynamic_array->size = 0;
        }
        else
        {
            *dynamic_array = (dynamic_array_ts){};
        }
    }
    return dynamic_array;
}

dynamic_array_ts *dynamic_array_new(size_t initial_size)
{
    return dynamic_array_init(malloc(sizeof(dynamic_array_ts)), initial_size);
}

void dynamic_array_destroy(dynamic_array_ts *dynamic_array)
{
    if (dynamic_array)
    {
        for (size_t i = dynamic_array->len; i > 0; i--)
        {
            free(dynamic_array->items[i - 1]);
        }
        free(dynamic_array->items);
        dynamic_array->items = NULL;
        dynamic_array->len = 0;
        dynamic_array->size = 0;
    }
}

void dynamic_array_free(dynamic_array_ts **dynamic_array)
{
    if (*dynamic_array)
    {
        free(*dynamic_array);
        *dynamic_array = NULL;
    }
}

unsigned dynamic_array_append(dynamic_array_ts *dynamic_array, char *line)
{
    if (dynamic_array && line)
    {
        size_t len = dynamic_array->len;
        size_t size = dynamic_array->size;

        if (len >= size)
        {
            size_t new_size = size * 2;
            if (new_size <= size)
            {
                fprintf(stderr, "Error: Size overflow in dynamic array.\n");
                return 0;
            }

            char **new_items = realloc(dynamic_array->items, new_size * sizeof(char *));
            if (new_items)
            {
                dynamic_array->items = new_items;
                dynamic_array->size = new_size;
            }
            else
            {
                fprintf(stderr, "Error: realloc failed in dynamic array.\n");
                return 0;
            }
        }

        char *line_copy = strdup(line);
        if (!line_copy)
        {
            fprintf(stderr, "Error: strdup failed in dynamic array.\n");
            return 0;
        }
        dynamic_array->items[len] = line_copy;
        dynamic_array->len = len + 1;
        return 1;
    }

    return 0;
}

char *dynamic_array_pop(dynamic_array_ts *dynamic_array)
{
    char *popped = NULL;
    if (dynamic_array)
    {
        size_t len = dynamic_array->len;
        if (len == 0)
        {
            fprintf(stderr, "Error: There are no items to pop.\n");
            return popped;
        }

        char *item = dynamic_array->items[len - 1];
        if (!item)
        {
            fprintf(stderr, "Error: Failed to pop item at index %zu.\n", len - 1);
            return popped;
        }

        popped = strdup(item);
        if (!popped)
        {
            fprintf(stderr, "Error: strdup failed.\n");
            return popped;
        }

        free(item);

        dynamic_array->items[len - 1] = NULL;

        dynamic_array->len = len - 1;
    }
    return popped;
}
