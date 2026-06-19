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
   Tests for ft_strmapi
   ------------------------------------------------------------------ */
/* Helper functions for ft_strmapi tests */
static char identity(unsigned int i, char c)
{
    (void)i;
    return (c);
}

static char to_upper(unsigned int i, char c)
{
    (void)i;
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
}

static char add_index(unsigned int i, char c)
{
    return (c + i);
}

static char transform(unsigned int i, char c)
{
    if (i % 2 == 0)
        return (c);
    else
        return (c + 1);
}

static void test_strmapi(void)
{
    printf("\n--- Testing ft_strmapi ---\n");

    struct {
        const char *s;
        char (*f)(unsigned int, char);
        const char *expected;
    } cases[] = {
        {"", identity, ""},
        {"hello", identity, "hello"},
        {"hello", to_upper, "HELLO"},
        {"abc", add_index, "ace"},   /* a+0 = 'a', b+1 = 'c', c+2 = 'e' */
        {"abc", transform, "acc"},   /* a unchanged, b+1 = 'c', c unchanged -> "ace" */
        {"xyz", add_index, "xz|"},   /* x+0='x', y+1='z', z+2='|'? Actually z+2 = 124 = '|', but test expects char values; we'll compute with a simple check */
        {NULL, NULL, NULL} /* sentinel */
    };

    for (int i = 0; cases[i].s != NULL; i++)
    {
        const char *s = cases[i].s;
        char (*f)(unsigned int, char) = cases[i].f;
        const char *exp = cases[i].expected;

        char *result = ft_strmapi(s, f);

        /* Ensure result is not NULL (we don't test allocation failure) */
        TEST_ASSERT(result != NULL, "ft_strmapi returned NULL");

        /* Compare with expected */
        char msg[256];
        snprintf(msg, sizeof(msg), "ft_strmapi mismatch for '%s'", s);
        TEST_ASSERT(strcmp(result, exp) == 0, msg);

        /* Check null-termination */
        size_t len = strlen(result);
        TEST_ASSERT(result[len] == '\0', "ft_strmapi missing null terminator");

        /* Verify that f was called with the correct indices by checking if
           the result matches a manual application */
        char manual[256];
        size_t j = 0;
        while (s[j])
        {
            manual[j] = f(j, s[j]);
            j++;
        }
        manual[j] = '\0';
        TEST_ASSERT(strcmp(result, manual) == 0, "ft_strmapi result differs from manual application");

        free(result);
    }

    /* Additional edge case: string with special characters (non-ASCII) */
    const char *special = "café";
    char *result = ft_strmapi(special, identity);
    TEST_ASSERT(result != NULL, "ft_strmapi returned NULL on special chars");
    TEST_ASSERT(strcmp(result, special) == 0, "ft_strmapi identity on special chars");
    free(result);
}

int main(void) {

    test_strmapi();          /* <-- add this line */
    print_summary();
    return (g_failed_tests != 0);
}
