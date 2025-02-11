#include "dynamic_array.h"
#include <assert.h>

void test_dynamic_array_init()
{
    dynamic_array_ts array;
    dynamic_array_init(&array, 2);
    assert(array.size == 2);
    assert(array.len == 0);
    printf("dynamic_array_init passed\n");
}

void test_dynamic_array_append()
{
    dynamic_array_ts array;
    dynamic_array_init(&array, 2);

    char *line = "Item 1";
    unsigned result = dynamic_array_append(&array, line);
    assert(result == 1);
    assert(array.len == 1);
    assert(array.size == 2);
    assert(array.items[0] != NULL);
    printf("dynamic_array_append passed\n");
}

void test_dynamic_array_pop()
{
    dynamic_array_ts array;
    dynamic_array_init(&array, 2);
    dynamic_array_append(&array, "Item 1");
    dynamic_array_append(&array, "Item 2");

    char *popped_item = dynamic_array_pop(&array);
    assert(popped_item != NULL);
    assert(array.len == 1);
    assert(array.size == 2);
    printf("dynamic_array_pop passed\n");

    free(popped_item);
}

void test_dynamic_array_destroy()
{
    dynamic_array_ts array;
    dynamic_array_init(&array, 2);
    dynamic_array_append(&array, "Item 1");

    dynamic_array_destroy(&array);
    assert(array.items == NULL);
    assert(array.size == 0);
    assert(array.len == 0);
    printf("dynamic_array_destroy passed\n");
}

int main()
{
    test_dynamic_array_init();
    test_dynamic_array_append();
    test_dynamic_array_pop();
    test_dynamic_array_destroy();

    return 0;
}
