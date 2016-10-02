#include <lcthw/bstree.h> 
#include <lcthw/bstrlib.h>
#include "minunit.h"  

// BSTree *map = BSTree_create(NULL); 

struct tagbstring test1 = bsStatic("test data 1"); 
struct tagbstring test2 = bsStatic("test data 2"); 
struct tagbstring test3 = bsStatic("test data 3"); 
struct tagbstring test4 = bsStatic("test data 4"); 
struct tagbstring test5 = bsStatic("test data 5"); 
struct tagbstring test6 = bsStatic("test data 6");
struct tagbstring test7 = bsStatic("test data 7"); 
struct tagbstring test8 = bsStatic("test data 8"); 
struct tagbstring test9 = bsStatic("test data 9"); 
struct tagbstring test10 = bsStatic("test data 10"); 
struct tagbstring test11 = bsStatic("test data 11"); 
struct tagbstring test12 = bsStatic("test data 12");

struct tagbstring expect1 = bsStatic("THE VALUE 1"); 
struct tagbstring expect2 = bsStatic("THE VALUE 2"); 
struct tagbstring expect3 = bsStatic("THE VALUE 3"); 
struct tagbstring expect4 = bsStatic("THE VALUE 4"); 
struct tagbstring expect5 = bsStatic("THE VALUE 5"); 
struct tagbstring expect6 = bsStatic("THE VALUE 6"); 
struct tagbstring expect7 = bsStatic("THE VALUE 7"); 
struct tagbstring expect8 = bsStatic("THE VALUE 8"); 
struct tagbstring expect9 = bsStatic("THE VALUE 9"); 
struct tagbstring expect10 = bsStatic("THE VALUE 10"); 
struct tagbstring expect11 = bsStatic("THE VALUE 11"); 
struct tagbstring expect12 = bsStatic("THE VALUE 12"); 

char *test_bfs()
{
    return NULL; 
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bfs); 

    return NULL;
}

RUN_TESTS(all_tests);

// int set_vals(BStree *map) 
// {
// 	int rc = BSTree_set(map, &test1, &expect1); 
// 	rc = BSTree_set(map, &test2, )
// }