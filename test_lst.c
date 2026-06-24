#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libft.h"

// global test helpers
static int g_total_tests = 0;
static int g_failed_tests = 0;

#define TEST_ASSERT(condition, msg) do { \
    g_total_tests++; \
    if (!(condition)) { \
        fprintf(stderr, "FAIL: %s\n", msg); \
        g_failed_tests++; \
    } \
} while (0)

static void print_summary(void) {
    printf("\n===== SUMMARY =====\n");
    printf("Total tests  : %d\n", g_total_tests);
    printf("Passed       : %d\n", g_total_tests - g_failed_tests);
    printf("Failed       : %d\n", g_failed_tests);
    if (g_failed_tests == 0)
        printf("All tests passed!\n");
    else
        printf("Some tests failed.\n");
}

// helpers
// new node with integer
static t_list *create_node_int(int value) {
    int *content = malloc(sizeof(int));
    if (!content) return NULL;
    *content = value;
    return ft_lstnew(content);
}

// delete function
static void delete_int(void *content) {
    free(content);
}

// linked list from int array
static t_list *list_from_array(int *arr, int size) {
    t_list *head = NULL;
    t_list *tail = NULL;
    for (int i = 0; i < size; i++) {
        t_list *node = create_node_int(arr[i]);
        if (!node) {
            ft_lstclear(&head, delete_int);
            return NULL;
        }
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
    }
    return head;
}

// helpers for itter
static void add_ten(void *content) {
    int *val = (int *)content;
    *val += 10;
}

static void *multiply_by_2(void *content) {
    int *new = malloc(sizeof(int));
    if (!new)
        return NULL;
    *new = (*(int *)content) * 2;
    return new;
}

// static void *map_fail_on_3(void *content) {
//     int val = *(int *)content;
//     if (val == 3) {
//         return NULL;
//     }
//     int *new = malloc(sizeof(int));
//     if (!new)
//         return NULL;
//     *new = val * 2;
//     return new;
// }

// TESTS

// lst new
static void test_lstnew(void) {
    printf("\n--- Testing ft_lstnew ---\n");
    int *content = malloc(sizeof(int));
    *content = 42;
    t_list *node = ft_lstnew(content);
    TEST_ASSERT(node != NULL, "ft_lstnew returned NULL");
    TEST_ASSERT(node->content == content, "ft_lstnew content not set correctly");
    TEST_ASSERT(*(int *)node->content == 42, "ft_lstnew content value mismatch");
    TEST_ASSERT(node->next == NULL, "ft_lstnew next not NULL");
    free(node->content);
    free(node);
}

//lst add front
static void test_lstadd_front(void) {
    printf("\n--- Testing ft_lstadd_front ---\n");
    t_list *list = NULL;
    t_list *node1 = create_node_int(1);
    t_list *node2 = create_node_int(2);

    ft_lstadd_front(&list, node1);
    TEST_ASSERT(list == node1, "add_front to empty list failed");
    TEST_ASSERT(list->next == NULL, "add_front to empty list: next not NULL");

    ft_lstadd_front(&list, node2);
    TEST_ASSERT(list == node2, "add_front to non-empty list failed");
    TEST_ASSERT(list->next == node1, "add_front order wrong");
    TEST_ASSERT(list->next->next == NULL, "add_front order wrong");

    ft_lstclear(&list, delete_int);
}

// lst size
static void test_lstsize(void) {
    printf("\n--- Testing ft_lstsize ---\n");
    int arr1[] = {1, 2, 3};
    t_list *list1 = list_from_array(arr1, 3);
    TEST_ASSERT(ft_lstsize(list1) == 3, "ft_lstsize with 3 nodes failed");

    int arr2[] = {42};
    t_list *list2 = list_from_array(arr2, 1);
    TEST_ASSERT(ft_lstsize(list2) == 1, "ft_lstsize with 1 node failed");

    t_list *list3 = NULL;
    TEST_ASSERT(ft_lstsize(list3) == 0, "ft_lstsize with NULL failed");

    ft_lstclear(&list1, delete_int);
    ft_lstclear(&list2, delete_int);
}

// lst last
static void test_lstlast(void) {
    printf("\n--- Testing ft_lstlast ---\n");
    int arr[] = {1, 2, 3, 4};
    t_list *list = list_from_array(arr, 4);
    t_list *last = ft_lstlast(list);
    TEST_ASSERT(last != NULL, "ft_lstlast returned NULL for non-empty list");
    TEST_ASSERT(*(int *)last->content == 4, "ft_lstlast wrong node");

    /* Single node */
    t_list *single = create_node_int(99);
    TEST_ASSERT(ft_lstlast(single) == single, "ft_lstlast with single node failed");

    /* Empty list */
    TEST_ASSERT(ft_lstlast(NULL) == NULL, "ft_lstlast with NULL should return NULL");

    ft_lstclear(&list, delete_int);
    free(single->content);
    free(single);
}

// lst add back
static void test_lstadd_back(void) {
    printf("\n--- Testing ft_lstadd_back ---\n");
    t_list *list = NULL;
    t_list *node1 = create_node_int(1);
    t_list *node2 = create_node_int(2);
    t_list *node3 = create_node_int(3);

    ft_lstadd_back(&list, node1);
    TEST_ASSERT(list == node1, "add_back to empty list failed");
    TEST_ASSERT(list->next == NULL, "add_back to empty list: next not NULL");

    ft_lstadd_back(&list, node2);
    TEST_ASSERT(list == node1, "add_back changed head");
    TEST_ASSERT(list->next == node2, "add_back order wrong");
    TEST_ASSERT(list->next->next == NULL, "add_back order wrong");

    ft_lstadd_back(&list, node3);
    TEST_ASSERT(list->next->next == node3, "add_back order wrong");
    TEST_ASSERT(list->next->next->next == NULL, "add_back order wrong");

    ft_lstclear(&list, delete_int);
}

// lst del one
static void test_lstdelone(void) {
    printf("\n--- Testing ft_lstdelone ---\n");

    t_list *node1 = create_node_int(1);
    t_list *node2 = create_node_int(2);
    node1->next = node2;

    ft_lstdelone(node1, delete_int);

    TEST_ASSERT(node2->next == NULL, "ft_lstdelone modified next of next node");
    TEST_ASSERT(*(int *)node2->content == 2, "ft_lstdelone corrupted next node");

    free(node2->content);
    free(node2);
}

// lst clear
static void test_lstclear(void) {
    printf("\n--- Testing ft_lstclear ---\n");
    int arr[] = {1, 2, 3, 4, 5};
    t_list *list = list_from_array(arr, 5);
    TEST_ASSERT(list != NULL, "ft_lstclear: list creation failed");

    ft_lstclear(&list, delete_int);
    TEST_ASSERT(list == NULL, "ft_lstclear did not set pointer to NULL");

    ft_lstclear(NULL, delete_int);
}

/* ft_lstiter */
static void test_lstiter(void) {
    printf("\n--- Testing ft_lstiter ---\n");
    int arr[] = {1, 2, 3};
    t_list *list = list_from_array(arr, 3);

    ft_lstiter(list, add_ten);

    int expected[] = {11, 12, 13};
    t_list *cur = list;
    int i = 0;
    int ok = 1;
    while (cur) {
        if (*(int *)cur->content != expected[i]) {
            ok = 0;
            break;
        }
        cur = cur->next;
        i++;
    }
    TEST_ASSERT(ok && i == 3, "ft_lstiter failed to apply function");

    ft_lstiter(NULL, add_ten);
    TEST_ASSERT(1 == 1, "ft_lstiter(NULL) did not crash");

    ft_lstclear(&list, delete_int);
}

// lst map
static void test_lstmap(void) {
    printf("\n--- Testing ft_lstmap ---\n");
    int arr[] = {1, 2, 3, 4};
    t_list *list = list_from_array(arr, 4);

    t_list *new_list = ft_lstmap(list, multiply_by_2, delete_int);
    TEST_ASSERT(new_list != NULL, "ft_lstmap returned NULL");
    int expected[] = {2, 4, 6, 8};
    t_list *cur = new_list;
    int i = 0;
    int ok = 1;
    while (cur) {
        if (*(int *)cur->content != expected[i]) {
            ok = 0;
            break;
        }
        cur = cur->next;
        i++;
    }
    TEST_ASSERT(ok && i == 4, "ft_lstmap content mismatch");

    cur = list;
    int orig[] = {1, 2, 3, 4};
    i = 0;
    ok = 1;
    while (cur) {
        if (*(int *)cur->content != orig[i]) {
            ok = 0;
            break;
        }
        cur = cur->next;
        i++;
    }
    TEST_ASSERT(ok && i == 4, "ft_lstmap modified original list");

    t_list *empty = NULL;
    t_list *new_empty = ft_lstmap(empty, multiply_by_2, delete_int);
    TEST_ASSERT(new_empty == NULL, "ft_lstmap with NULL should return NULL");

    //t_list *fail_list = list_from_array(arr, 4);
    //t_list *result = ft_lstmap(fail_list, map_fail_on_3, delete_int);
    //TEST_ASSERT(result == NULL, "ft_lstmap should return NULL when mapping fails");

    // cur = fail_list;
    // i = 0;
    // ok = 1;
    // while (cur) {
    //     if (*(int *)cur->content != orig[i]) {
    //         ok = 0;
    //         break;
    //     }
    //     cur = cur->next;
    //     i++;
    // }
    // TEST_ASSERT(ok && i == 4, "ft_lstmap modified original list on failure");

    ft_lstclear(&list, delete_int);
    ft_lstclear(&new_list, delete_int);
    // ft_lstclear(&fail_list, delete_int);
}

int main(void) {
    test_lstnew();
    test_lstadd_front();
    test_lstsize();
    test_lstlast();
    test_lstadd_back();
    test_lstdelone();
    test_lstclear();
    test_lstiter();
    test_lstmap();

    print_summary();
    return (g_failed_tests != 0);
}
