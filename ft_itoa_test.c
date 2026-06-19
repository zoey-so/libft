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
   Tests for ft_itoa
   ------------------------------------------------------------------ */
static void test_itoa(void)
{
    printf("\n--- Testing ft_itoa ---\n");

    struct {
        int n;
        const char *expected;  /* optional; if NULL we generate with snprintf */
    } cases[] = {
        {0, "0"},
        {1, "1"},
        {-1, "-1"},
        {42, "42"},
        {-42, "-42"},
        {123456, "123456"},
        {-123456, "-123456"},
        {2147483647, "2147483647"},   /* INT_MAX */
        {-2147483648, "-2147483648"}, /* INT_MIN */
        {5, "5"},
        {-5, "-5"},
        {10, "10"},
        {-10, "-10"},
        {100, "100"},
        {-100, "-100"}
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++)
    {
        int n = cases[i].n;
        const char *exp = cases[i].expected;

        char *result = ft_itoa(n);

        /* Ensure result is not NULL (we don't test allocation failure) */
        TEST_ASSERT(result != NULL, "ft_itoa returned NULL");

        /* Compare with expected string */
        char msg[256];
        snprintf(msg, sizeof(msg), "ft_itoa(%d) mismatch, exp = %s, res = %s", n, exp, result);
        TEST_ASSERT(strcmp(result, exp) == 0, msg);

        /* Also test using snprintf for additional safety (optional) */
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%d", n);
        TEST_ASSERT(strcmp(result, buffer) == 0, "ft_itoa vs snprintf");

        free(result);
    }

    /* Additional edge case: test that the string is properly null-terminated */
    int test_vals[] = {0, -1, INT_MAX, INT_MIN};
    for (size_t i = 0; i < sizeof(test_vals) / sizeof(test_vals[0]); i++)
    {
        char *result = ft_itoa(test_vals[i]);
        TEST_ASSERT(result != NULL, "ft_itoa returned NULL");
        size_t len = strlen(result);
        /* Check that the last character is '\0' (strlen already does this) */
        TEST_ASSERT(result[len] == '\0', "ft_itoa missing null terminator");
        free(result);
    }
}

int main(void) {

    test_itoa();          /* <-- add this line */
    print_summary();
    return (g_failed_tests != 0);
}
