#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
static List *list2 = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
    list = List_create();
    list2 = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;
}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

char *test_copy()
{
    mu_assert(List_count(list2) == 0, "Wrong count beginning copy.");

    List_push(list2, test1);
    List_push(list2, test2);
    List_push(list2, test3);
    mu_assert(List_count(list2) == 3, "Wrong count on push.");

    List *copy_list = List_copy(list2);

    mu_assert(List_first(list2) == List_first(copy_list), "First element copy failed.");
    mu_assert(List_last(list2) == List_last(copy_list), "Last element copy failed.");

    // Changing one element
    list2->first->value = "TESTING";
    mu_assert(List_first(list2) != List_first(copy_list), "Improperly copied.");

    return NULL;
}

char *test_join()
{
    mu_assert(List_count(list2) == 3, "Wrong count beginning copy.");

    // Just going to join list2 twice
    List *joined_list = List_join(list2, list2);

    mu_assert(List_count(joined_list) == 6, "Wrong count after join.");
    mu_assert(List_first(list2) == List_first(joined_list),
            "Wrong first element on join.");
    mu_assert(List_count(joined_list) == List_count(list2) + List_count(list2),
            "Wrong count after join.");

    return NULL;
}

char *test_split()
{

    List *split_list = List_create();
    List_push(split_list, test1);
    List_push(split_list, test2);
    List_push(split_list, test3);
    List_push(split_list, test1);
    List_push(split_list, test2);
    List_push(split_list, test3);
    List *split1 = List_create();
    List *split2 = List_create();

    List_split(split_list, 2, split1, split2);

    mu_assert(List_count(split1) == 3, "Wrong count on split1.");
    mu_assert(List_count(split2) == 3, "Wrong count on split2.");
    mu_assert(List_first(split1) == test1, "Wrong first value on split1");
    mu_assert(List_first(split2) == test1, "Wrong first value on split2")

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_copy);
    mu_run_test(test_join);
    mu_run_test(test_split);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
