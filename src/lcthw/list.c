#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <stdio.h>
#include <string.h>

List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_destroy(List * list)
{

    LIST_FOREACH(list, first, next, cur) {
        if (cur->prev) {
            free(cur->prev);
        }
    }

    free(list->last);
    free(list);
}

void List_clear(List * list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
    }
}

void List_clear_destroy(List * list)
{
    LIST_FOREACH(list, first, next, cur) {
        free(cur->value);
        if(cur->prev) {
            free(cur->prev);
        }
    }
    free(list->last);
    free(list);

}

void List_push(List * list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List * list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List * list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List * list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List * list, ListNode * node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if (node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if (node == list->first) {
        list->first = node->next;
        check(list->first != NULL,
                "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL,
                "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

List *List_copy(List * list)
{
    List * copy_list = List_create();

    LIST_FOREACH(list, first, next, cur) {
        List_push(copy_list, cur->value);
    }

    return copy_list;
}

void *List_add(List * from_list, List * to_list)
{
    LIST_FOREACH(from_list, first, next, cur) {
        List_push(to_list, cur->value);
    }

    return NULL;
}

List *List_join(List * list1, List * list2)
{
    List *joined_list = List_create();

    List_add(list1, joined_list);
    List_add(list2, joined_list);

    return joined_list;
}

void *List_split(List * list, int index, List * list1, List * list2)
{
    int counter = 0;

    check(index < List_count(list) && index > 0 && List_count(list) > 1,
        "Index out of bounds: %d", index);

    LIST_FOREACH(list, first, next, cur) {
        if (counter <= index) {
            List_push(list1, cur->value);
        } else if (counter > index) {
            List_push(list2, cur->value);
        }
        counter++;
    }

    check(List_count(list1) > 0 && List_count(list2) > 0,
            "Improper splitting of lists (i.e. counts are less than 0)");

    return NULL;

error:
    return NULL;
}
