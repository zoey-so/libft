#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include "libft.h"
#include "libft_bonus.h"

/* ------------------------------------------------------------------
   Helper functions for testing and reporting
   ------------------------------------------------------------------ */
static int g_total_tests = 0;
static int g_failed_tests = 0;
#define TEST_ASSERT(condition, msg) do { \
    g_total_tests++; \
    if (!(condition)) { \
        fprintf(stderr, "FAIL: %s\n", msg); \
        g_failed_tests++; \
    } \
} while (0)


/* Print final summary */
static void print_summary(void) {
    printf("\n===== TEST SUMMARY =====\n");
    printf("Total tests  : %d\n", g_total_tests);
    printf("Passed       : %d\n", g_total_tests - g_failed_tests);
    printf("Failed       : %d\n", g_failed_tests);
    if (g_failed_tests == 0)
        printf("All tests passed!\n");
    else
        printf("Some tests failed.\n");
}


/* ------------------------------------------------------------------
   Tests for ft_split
   ------------------------------------------------------------------ */
static void test_split(void)
{
    printf("\n--- Testing ft_split ---\n");

    struct {
        const char *s;
        char c;
        const char **expected;  /* NULL‑terminated list of expected strings */
    } cases[] = {
        {"", ' ', (const char *[]){NULL}},
        {"   ", ' ', (const char *[]){NULL}},
        {"hello", ' ', (const char *[]){ "hello", NULL }},
        {" hello ", ' ', (const char *[]){ "hello", NULL }},
        {"  hello  world  ", ' ', (const char *[]){ "hello", "world", NULL }},
        {"a  b  c", ' ', (const char *[]){ "a", "b", "c", NULL }},
        {"a:b:c", ':', (const char *[]){ "a", "b", "c", NULL }},
        {"a::b", ':', (const char *[]){ "a", "b", NULL }},
        {":a:b:", ':', (const char *[]){ "a", "b", NULL }},
        {"abc", 'x', (const char *[]){ "abc", NULL }},
        {"xabcx", 'x', (const char *[]){ "abc", NULL }},
        {"xxx", 'x', (const char *[]){NULL}},
        {"a", ' ', (const char *[]){ "a", NULL }},
        {"a b c d e", ' ', (const char *[]){ "a", "b", "c", "d", "e", NULL }},
        {NULL, 0, NULL}  /* sentinel */
    };

    for (int i = 0; cases[i].s != NULL; i++)
    {
        const char *s = cases[i].s;
        char c = cases[i].c;
        const char **exp = cases[i].expected;

        char **result = ft_split(s, c);

        /* 1. Check that result is not NULL (we don't test allocation failure) */
        TEST_ASSERT(result != NULL, "ft_split returned NULL");

        /* 2. Count number of strings in result */
        int count = 0;
        while (result[count] != NULL)
            count++;

        /* 3. Count expected strings */
        int exp_count = 0;
        while (exp[exp_count] != NULL)
            exp_count++;

        /* 4. Compare count */
        char msg[256];
        snprintf(msg, sizeof(msg), "split count mismatch for '%s' (delimiter '%c')", s, c);
        TEST_ASSERT(count == exp_count, msg);

        /* 5. Compare each string */
        for (int j = 0; j < count; j++)
        {
            snprintf(msg, sizeof(msg), "string %d mismatch for '%s', result: '%s'", j, s, result[j]);
            TEST_ASSERT(strcmp(result[j], exp[j]) == 0, msg);
        }

        /* 6. Free allocated memory */
        for (int j = 0; j < count; j++)
            free(result[j]);
        free(result);
    }
}

int main(void) {

    test_split();          /* <-- add this line */
    print_summary();
    return (g_failed_tests != 0);
}
