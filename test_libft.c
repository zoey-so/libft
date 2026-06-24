/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smilch <smilch@student.42warsaw.pl>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 15:13:22 by smilch            #+#    #+#             */
/*   Updated: 2026/06/24 15:13:24 by smilch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
//#include <bsd/string.h>
#include <stdint.h>
#include "libft.h"

// Global test helpers
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
    printf("\n===== TEST SUMMARY =====\n");
    printf("Total tests  : %d\n", g_total_tests);
    printf("Passed       : %d\n", g_total_tests - g_failed_tests);
    printf("Failed       : %d\n", g_failed_tests);
    if (g_failed_tests == 0)
        printf("All tests passed!\n");
    else
        printf("Some tests failed.\n");
}

// ctype macros
static void test_ctype_macros(void) {
    int c;
    printf("\n--- Testing ctype macros ---\n");

    /* Test all values from -128 to 255 */
    for (c = -128; c <= 255; c++) {
        /* ft_isalpha */
        int expected = isalpha(c) ? 1 : 0;
        int got = ft_isalpha(c);
        TEST_ASSERT(got == expected,
                    "ft_isalpha mismatch for c=");
        /* ft_isdigit */
        expected = isdigit(c) ? 1 : 0;
        got = ft_isdigit(c);
        TEST_ASSERT(got == expected,
                    "ft_isdigit mismatch for c=");
        /* ft_isprint */
        expected = isprint(c) ? 1 : 0;
        got = ft_isprint(c);
        TEST_ASSERT(got == expected,
                    "ft_isprint mismatch for c=");
        /* ft_isalnum */
        expected = isalnum(c) ? 1 : 0;
        got = ft_isalnum(c);
        TEST_ASSERT(got == expected,
                    "ft_isalnum mismatch for c=");
        /* ft_isascii */
        expected = (c >= 0 && c <= 127) ? 1 : 0;
        got = ft_isascii(c);
        TEST_ASSERT(got == expected,
                    "ft_isascii mismatch for c=");
    }

    /* Test some values outside -128..255 range (e.g., 300, -300) */
    int extra_vals[] = {300, -300, EOF, INT_MAX, INT_MIN};
    for (int i = 0; i < (int)(sizeof(extra_vals)/sizeof(extra_vals[0])); i++) {
        c = extra_vals[i];
        int exp_a = isalpha(c) ? 1 : 0;
        int got_a = ft_isalpha(c);
        TEST_ASSERT(got_a == exp_a, "ft_isalpha with out-of-range");
        int exp_d = isdigit(c) ? 1 : 0;
        int got_d = ft_isdigit(c);
        TEST_ASSERT(got_d == exp_d, "ft_isdigit with out-of-range");
        int exp_p = isprint(c) ? 1 : 0;
        int got_p = ft_isprint(c);
        TEST_ASSERT(got_p == exp_p, "ft_isprint with out-of-range");
        int exp_al = isalnum(c) ? 1 : 0;
        int got_al = ft_isalnum(c);
        TEST_ASSERT(got_al == exp_al, "ft_isalnum with out-of-range");
        int exp_asc = (c >= 0 && c <= 127) ? 1 : 0;
        int got_asc = ft_isascii(c);
        TEST_ASSERT(got_asc == exp_asc, "ft_isascii with out-of-range");
    }
}

// ft_tolower / ft_toupper
static void test_tolower_toupper(void) {
    printf("\n--- Testing ft_tolower / ft_toupper ---\n");
    int c;
    for (c = -128; c <= 255; c++) {
        int exp = tolower(c);
        int got = ft_tolower(c);
		if (exp != got)
			printf("tested val: %d, exp = %d, got = %d\n", c, exp, got);
        TEST_ASSERT(got == exp, "ft_tolower mismatch");
        exp = toupper(c);
        got = ft_toupper(c);
		if (exp != got)
			printf("tested val: %d, exp = %d, got = %d\n", c, exp, got);
        TEST_ASSERT(got == exp, "ft_toupper mismatch");
    }
}

//ft_atoi
static void test_atoi(void) {
    printf("\n--- Testing ft_atoi ---\n");
    const char *test_cases[] = {
        "0", "1", "-1", "+1", "  -123", "  456", "123abc", "abc",
        "\t\n\v\f\r  -789", "2147483647", "-2147483648",
        "999999999999", "-999999999999", "", "   +  123"
    };
    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        const char *s = test_cases[i];
        int exp = atoi(s);
        int got = ft_atoi(s);
        TEST_ASSERT(got == exp, "ft_atoi mismatch for input");
    }
}

// ft_bzero
static void test_bzero(void) {
    printf("\n--- Testing ft_bzero ---\n");
    char buf1[256], buf2[256];
    size_t sizes[] = {0, 1, 5, 10, 100, 255, 256};
    for (size_t i = 0; i < sizeof(sizes)/sizeof(sizes[0]); i++) {
        size_t n = sizes[i];
        memset(buf1, 0xAA, sizeof(buf1));
        memset(buf2, 0xAA, sizeof(buf2));
        ft_bzero(buf1, n);
        bzero(buf2, n);
        TEST_ASSERT(memcmp(buf1, buf2, sizeof(buf1)) == 0,
                    "ft_bzero mismatch for size");
    }
}

//ft_calloc
static void test_calloc(void) {
    printf("\n--- Testing ft_calloc ---\n");
    /* Test with various count, size combinations */
    size_t tests[][2] = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}, {5, 10}, {10, 5}, {100, 1}
    };
    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        size_t count = tests[i][0];
        size_t size = tests[i][1];
        void *p1 = ft_calloc(count, size);
        void *p2 = calloc(count, size);
        if (p1 == NULL || p2 == NULL) {
            if (p1 != p2) {
                TEST_ASSERT(0, "calloc NULL mismatch");
            }
        } else {
            /* Compare allocated memory content (should be zero) */
            size_t total = count * size;
            TEST_ASSERT(memcmp(p1, p2, total) == 0,
                        "ft_calloc memory content mismatch");
            free(p1);
            free(p2);
        }
    }
    /* Test with huge allocation (should return NULL) */
    void *p = ft_calloc(SIZE_MAX, SIZE_MAX);
    TEST_ASSERT(p == NULL, "ft_calloc should fail for over size_max");
}

//ft_memchr
static void test_memchr(void) {
    printf("\n--- Testing ft_memchr ---\n");
    unsigned char buf[64];
    for (int i = 0; i < 64; i++) buf[i] = i;
    /* Search various chars and lengths */
    size_t lens[] = {0, 1, 5, 10, 32, 64};
    int chars[] = {0, 1, 10, 63, 64, 255, -1, 200};
    for (size_t li = 0; li < sizeof(lens)/sizeof(lens[0]); li++) {
        size_t n = lens[li];
        for (size_t ci = 0; ci < sizeof(chars)/sizeof(chars[0]); ci++) {
            int c = chars[ci];
            void *exp = memchr(buf, c, n);
            void *got = ft_memchr(buf, c, n);
            TEST_ASSERT(exp == got, "ft_memchr mismatch");
        }
    }
}

//ft_memcmp
static void test_memcmp(void) {
    printf("\n--- Testing ft_memcmp ---\n");
    unsigned char a[64], b[64];
    for (int i = 0; i < 64; i++) { a[i] = i; b[i] = i; }
    /* Equal blocks */
    TEST_ASSERT(ft_memcmp(a, b, 64) == 0, "memcmp equal");
    /* Different at position */
    b[10] = 200;
    int exp = memcmp(a, b, 64);
    int got = ft_memcmp(a, b, 64);
    TEST_ASSERT((exp > 0 && got > 0) || (exp < 0 && got < 0) || (exp == 0 && got == 0),
                "memcmp sign mismatch");
    /* Zero length */
    TEST_ASSERT(ft_memcmp(a, b, 0) == 0, "memcmp zero length");
    /* Compare with n less than difference */
    TEST_ASSERT(ft_memcmp(a, b, 10) == 0, "memcmp with n before difference");
    /* Edge: compare with NULL? Not defined */
}

// ft_memcpy
static void test_memcpy(void) {
    printf("\n--- Testing ft_memcpy ---\n");
    unsigned char src[128], dst1[128], dst2[128];
    for (int i = 0; i < 128; i++) src[i] = i;
    /* Copy various lengths */
    size_t lens[] = {0, 1, 5, 10, 64, 128};
    for (size_t li = 0; li < sizeof(lens)/sizeof(lens[0]); li++) {
        size_t n = lens[li];
        memset(dst1, 0xAA, sizeof(dst1));
        memset(dst2, 0xAA, sizeof(dst2));
        void *r1 = ft_memcpy(dst1, src, n);
        void *r2 = memcpy(dst2, src, n);
        TEST_ASSERT(r1 == dst1 && r2 == dst2, "memcpy return value mismatch");
        TEST_ASSERT(memcmp(dst1, dst2, sizeof(dst1)) == 0,
                    "memcpy content mismatch");
    }
}

//ft_memmove
static void test_memmove(void) {
    printf("\n--- Testing ft_memmove ---\n");
    unsigned char buf1[128], buf2[128];
    /* Fill both with same pattern */
    for (int i = 0; i < 128; i++) buf1[i] = buf2[i] = i;
    /* Overlap: move forward (src before dst) */
    size_t src_start = 10, dst_start = 20, len = 30;
    void *r1 = ft_memmove(buf1 + dst_start, buf1 + src_start, len);
    void *r2 = memmove(buf2 + dst_start, buf2 + src_start, len);
    TEST_ASSERT(r1 == (buf1 + dst_start) && r2 == (buf2 + dst_start),
                "memmove return forward");
    TEST_ASSERT(memcmp(buf1, buf2, 128) == 0,
                "memmove forward content");

    /* Overlap: move backward (src after dst) */
    src_start = 30; dst_start = 10; len = 25;
    r1 = ft_memmove(buf1 + dst_start, buf1 + src_start, len);
    r2 = memmove(buf2 + dst_start, buf2 + src_start, len);
    TEST_ASSERT(memcmp(buf1, buf2, 128) == 0,
                "memmove backward content");

    /* No overlap */
    src_start = 0; dst_start = 50; len = 40;
    r1 = ft_memmove(buf1 + dst_start, buf1 + src_start, len);
    r2 = memmove(buf2 + dst_start, buf2 + src_start, len);
    TEST_ASSERT(memcmp(buf1, buf2, 128) == 0,
                "memmove non-overlap");

    /* Zero length */
    ft_memmove(buf1, buf1 + 10, 0);
    memmove(buf2, buf2 + 10, 0);
    TEST_ASSERT(memcmp(buf1, buf2, 128) == 0,
                "memmove zero length");
}

//ft_memset
static void test_memset(void) {
    printf("\n--- Testing ft_memset ---\n");
    unsigned char buf1[256], buf2[256];
    int vals[] = {0, 1, 42, 255, -1, 200};
    size_t lens[] = {0, 1, 5, 10, 100, 255, 256};
    for (size_t vi = 0; vi < sizeof(vals)/sizeof(vals[0]); vi++) {
        int c = vals[vi];
        for (size_t li = 0; li < sizeof(lens)/sizeof(lens[0]); li++) {
            size_t n = lens[li];
            memset(buf1, 0xAA, sizeof(buf1));
            memset(buf2, 0xAA, sizeof(buf2));
            void *r1 = ft_memset(buf1, c, n);
            void *r2 = memset(buf2, c, n);
            TEST_ASSERT(r1 == buf1 && r2 == buf2,
                        "memset return mismatch");
            TEST_ASSERT(memcmp(buf1, buf2, sizeof(buf1)) == 0,
                        "memset content mismatch");
        }
    }
}

//ft_strlen
static void test_strlen(void) {
    printf("\n--- Testing ft_strlen ---\n");
    const char *strs[] = {"", "a", "hello", "long string with spaces",
                          "abc\0def", "\0"};
    for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); i++) {
        const char *s = strs[i];
        size_t exp = strlen(s);
        size_t got = ft_strlen(s);
        TEST_ASSERT(exp == got, "ft_strlen mismatch");
    }
}

//ft_strdup
static void test_strdup(void) {
    printf("\n--- Testing ft_strdup ---\n");
    const char *strs[] = {"", "a", "hello world", "12345"};
    for (size_t i = 0; i < sizeof(strs)/sizeof(strs[0]); i++) {
        const char *s = strs[i];
        char *dup1 = ft_strdup(s);
        char *dup2 = strdup(s);
        if (dup1 == NULL || dup2 == NULL) {
            /* Both should be NULL if allocation fails (unlikely) */
            TEST_ASSERT(dup1 == dup2, "strdup NULL mismatch");
        } else {
            TEST_ASSERT(strcmp(dup1, dup2) == 0,
                        "ft_strdup content mismatch");
            TEST_ASSERT(ft_strlen(dup1) == strlen(dup2),
                        "ft_strdup length mismatch");
            free(dup1);
            free(dup2);
        }
    }
}

//ft_strlcpy
static void test_strlcpy(void) {
    printf("\n--- Testing ft_strlcpy ---\n");
    char dst1[64], dst2[64];
    const char *srcs[] = {"", "hello", "long string that will be truncated"};
    size_t sizes[] = {0, 1, 5, 10, 64};

    for (size_t si = 0; si < sizeof(srcs)/sizeof(srcs[0]); si++) {
        const char *src = srcs[si];
        size_t src_len = strlen(src);
        for (size_t di = 0; di < sizeof(sizes)/sizeof(sizes[0]); di++) {
            size_t size = sizes[di];

            /* Fill both with known pattern */
            memset(dst1, 0x00, sizeof(dst1));
            memset(dst2, 0x00, sizeof(dst2));
            size_t ret1 = ft_strlcpy(dst1, src, size);

            size_t ret2 = strlcpy(dst2, src, size);
            TEST_ASSERT(ret1 == src_len, "ft_strlcpy return value");
            TEST_ASSERT(ret1 == ret2, "return value mismatch with reference");
            if (size > 0) {
                TEST_ASSERT(dst1[size-1] == '\0', "null‑termination");
                size_t cmp_len = (size - 1 < src_len) ? size - 1 : src_len;
                TEST_ASSERT(memcmp(dst1, dst2, cmp_len) == 0,
                            "content mismatch");
            }
        }
    }
}

//ft_strlcat
static void test_strlcat(void) {
    printf("\n--- Testing ft_strlcat ---\n");
    char dst1[64], dst2[64];
    const char *src = "world";
    size_t sizes[] = {0, 1, 5, 10, 64};
    const char *init[] = {"", "hello", "hi"};
    for (size_t ii = 0; ii < sizeof(init)/sizeof(init[0]); ii++) {
        const char *init_s = init[ii];
        size_t init_len = strlen(init_s);
        for (size_t si = 0; si < sizeof(sizes)/sizeof(sizes[0]); si++) {
            size_t size = sizes[si];

            strcpy(dst1, init_s);
            strcpy(dst2, init_s);
            size_t ret1 = ft_strlcat(dst1, src, size);
			size_t ret2 = strlcat(dst2, src, size);
            TEST_ASSERT(ret1 == ret2, "ft_strlcat return value");
			TEST_ASSERT(memcmp(dst1, dst2, strlen(dst2 + 1)) == 0,
                            "ft_strlcat vs strlcat content");
            /* Check destination content */
            if (size > init_len) {
                /* Should have appended some chars */
                size_t app_len = size - init_len - 1;
                if (app_len > strlen(src)) app_len = strlen(src);
                /* Check that dst1 ends with src prefix */
                char *pos = dst1 + init_len;
                TEST_ASSERT(memcmp(pos, src, app_len) == 0,
                            "ft_strlcat append content");
                TEST_ASSERT(dst1[init_len + app_len] == '\0',
                            "ft_strlcat null-termination");
            } else {
                /* size <= init_len: nothing appended, dst unchanged */
                TEST_ASSERT(strcmp(dst1, init_s) == 0,
                            "ft_strlcat should not modify when size <= init_len");
            }
        }
    }
}

//ft_strncmp
static void test_strncmp(void) {
    printf("\n--- Testing ft_strncmp ---\n");
    struct {
        const char *s1;
        const char *s2;
        size_t n;
    } cases[] = {
        {"", "", 0},
        {"a", "a", 1},
        {"abc", "abc", 5},
        {"abc", "abd", 3},
        {"abc", "abcd", 4},
        {"abc", "abc", 2},
        {"abc", "abd", 1},
        {"abc", "abc", 0},
        {"", "a", 1},
        {"a", "", 1}
    };
    for (size_t i = 0; i < sizeof(cases)/sizeof(cases[0]); i++) {
        int exp = strncmp(cases[i].s1, cases[i].s2, cases[i].n);
        int got = ft_strncmp(cases[i].s1, cases[i].s2, cases[i].n);
        TEST_ASSERT(exp == got, "ft_strncmp mismatch");
    }
    /* Additional edge cases */
    TEST_ASSERT(ft_strncmp("", "a", 1) < 0, "empty vs a");
    TEST_ASSERT(ft_strncmp("a", "", 1) > 0, "a vs empty");
    TEST_ASSERT(ft_strncmp("", "", 0) == 0, "both empty");
    TEST_ASSERT(ft_strncmp("abc", "def", 0) == 0, "n=0");
}

//ft_strnstr
static void test_strnstr(void) {
    printf("\n--- Testing ft_strnstr ---\n");
    struct {
        const char *haystack;
        const char *needle;
        size_t len;
        const char *expected;  /* expected pointer or NULL */
    } cases[] = {
        {"hello world", "world", 11, "world"},
        {"hello world", "world", 5, NULL},
        {"hello world", "", 11, "hello world"},  /* empty needle returns haystack */
        {"", "hello", 0, NULL},
        {"abc", "abc", 3, "abc"},
        {"abc", "abc", 2, NULL},
        {"abc", "b", 3, "bc"},
        {"abc", "b", 1, NULL},
        {"abc", "d", 3, NULL},
        {"aaa", "aa", 3, "aaa"},
        {"aaab", "aa", 4, "aaab"},
        {"aaab", "aa", 2, NULL},
    };
    for (size_t i = 0; i < sizeof(cases)/sizeof(cases[0]); i++) {
        const char *hay = cases[i].haystack;
        const char *nee = cases[i].needle;
        size_t len = cases[i].len;
        char *exp = strnstr(hay, nee, len);
        char *got = ft_strnstr(hay, nee, len);
        /* Check pointer equality; if both NULL or point to same char */
        if (exp == NULL) {
            TEST_ASSERT(got == NULL, "ft_strnstr should return NULL");
			if (got != exp)
			{
				printf("got = %s, exp = %s len = %d\n", got, exp, (int)len);
				printf("hay = %s, need = %s\n", hay, nee);
			}
        } else {
            TEST_ASSERT(got == exp, "ft_strnstr pointer mismatch");
			if (got != exp)
			{
				printf("got = %s, exp = %s len = %d\n", got, exp, (int)len);
				printf("got_ptr = %p, exp_ptr = %p\n", got, exp);
				printf("hay = %s, need = %s\n", hay, nee);
			}
        }
    }
}
//ft_strchr
static void test_strchr(void) {
    printf("\n--- Testing ft_strchr ---\n");
    const char *s1 = "hello world";
    /* Existing characters */
    char chars[] = {'h', 'e', 'l', 'o', ' ', 'w', 'r', 'd'};
    for (size_t i = 0; i < sizeof(chars)/sizeof(chars[0]); i++) {
        int c = chars[i];
        TEST_ASSERT(ft_strchr(s1, c) == strchr(s1, c), "strchr existing");
    }
    /* Null terminator */
    TEST_ASSERT(ft_strchr(s1, '\0') == strchr(s1, '\0'), "strchr null terminator");
    /* Not found */
    TEST_ASSERT(ft_strchr(s1, 'x') == NULL, "strchr not found");
    /* Empty string */
    const char *empty = "";
    TEST_ASSERT(ft_strchr(empty, 'a') == NULL, "strchr empty not found");
    TEST_ASSERT(ft_strchr(empty, '\0') == (char*)empty, "strchr empty null");

    /* Values > 255 and negative – cast to unsigned char */
    TEST_ASSERT(ft_strchr(s1, 256) == strchr(s1, 256), "strchr c=256 (== '\\0')");
    TEST_ASSERT(ft_strchr(s1, -1) == strchr(s1, -1), "strchr c=-1 (== 255)");

    /* String containing byte 255 */
    unsigned char s2[10] = "abc";
    s2[3] = 255;
    s2[4] = '\0';
    TEST_ASSERT(ft_strchr((char*)s2, 255) == strchr((char*)s2, 255),
                "strchr char 255");
    TEST_ASSERT(ft_strchr((char*)s2, -1) == strchr((char*)s2, -1),
                "strchr c=-1 with 255");
}

//ft_strrchr
static void test_strrchr(void) {
    printf("\n--- Testing ft_strrchr ---\n");
    const char *s = "hello world";
    /* Search for existing chars */
    char chars[] = {'h', 'e', 'l', 'o', ' ', 'd', 'x', '\0'};
    for (size_t i = 0; i < sizeof(chars)/sizeof(chars[0]); i++) {
        int c = chars[i];
        char *exp = strrchr(s, c);
        char *got = ft_strrchr(s, c);
        TEST_ASSERT(exp == got, "ft_strrchr mismatch");
		if (got != exp)
			{
				printf("got = %s, exp = %s searched = %c\n", got, exp, c);
				printf("got_ptr = %p, exp_ptr = %p\n", got, exp);
			}
    }
    /* Empty string */
    const char *empty = "";
    TEST_ASSERT(ft_strrchr(empty, 'a') == NULL, "empty string, char not found");
    TEST_ASSERT(ft_strrchr(empty, '\0') == (char*)empty, "empty string, null char");
}

// ft_substr
static void test_substr(void)
{
    printf("\n--- Testing ft_substr ---\n");

    struct {
        const char *s;
        unsigned int start;
        size_t len;
        const char *expected;
    } cases[] = {
        {"hello", 0, 0, ""},
        {"hello", 0, 1, "h"},
        {"hello", 0, 5, "hello"},
        {"hello", 0, 10, "hello"},
        {"hello", 1, 3, "ell"},
        {"hello", 1, 0, ""},
        {"hello", 5, 0, ""},
        {"hello", 5, 5, ""},          /* start == len -> empty */
        {"hello", 6, 0, ""},          /* start > len -> empty */
        {"hello", 6, 5, ""},
        {"", 0, 0, ""},
        {"", 0, 5, ""},
        {"abcdef", 2, 4, "cdef"},
        {"abcdef", 2, 10, "cdef"},
        {"abcdef", 6, 0, ""},
        {"abcdef", 6, 5, ""},
        {"12345", 0, 3, "123"},
        {"12345", 3, 2, "45"},
        {"12345", 3, 0, ""},
        {"   ", 0, 3, "   "},
        {"   ", 1, 1, " "},
        {"   ", 3, 1, ""},
        {NULL, 0, 0, NULL} /* sentinel */
    };

    for (int i = 0; cases[i].s != NULL; i++)
    {
        const char *s = cases[i].s;
        unsigned int start = cases[i].start;
        size_t len = cases[i].len;
        const char *exp = cases[i].expected;

        /* Compute expected if not provided */
        char *expected = NULL;

            expected = strdup(exp);  /* strdup for consistency, will free later */

        if (!expected)
        {
            TEST_ASSERT(0, "Failed to allocate expected string");
            continue;
        }

        char *result = ft_substr(s, start, len);

        /* Ensure result is not NULL (allocation should succeed) */
        TEST_ASSERT(result != NULL, "ft_substr returned NULL");

        /* Compare */
        char msg[256];
        snprintf(msg, sizeof(msg), "ft_substr('%s', %u, %zu) mismatch", s, start, len);
        TEST_ASSERT(strcmp(result, expected) == 0, msg);

        /* Ensure result is a new allocation */
        TEST_ASSERT(result != s, "ft_substr returned original pointer");

        /* Check null-termination */
        size_t result_len = strlen(result);
        TEST_ASSERT(result[result_len] == '\0', "ft_substr missing null terminator");

        /* Free */
        free(result);
        free(expected);
    }
}

//ft_strtrim
static void test_strtrim(void)
{
    printf("\n--- Testing ft_strtrim ---\n");

    struct {
        const char *s1;
        const char *set;
        const char *expected;
    } cases[] = {
        /* Basic cases */
        {"", " ", ""},
        {"   ", " ", ""},
        {"hello", " ", "hello"},
        {"  hello  ", " ", "hello"},
        {"\t\nhello\t\n", "\t\n", "hello"},
        {"  hello world  ", " ", "hello world"},
        {"abc", "abc", ""},                    /* all chars in set */
        {"abc", "def", "abc"},                 /* none in set */
        {"abc", "abcd", ""},                   /* all chars in set (includes extra) */
        {"abc", "ad", "bc"},                   /* 'a' trimmed from front, but 'c'? Actually 'c' not in set -> "bc" */
        {"abc", "ac", "b"},                    /* 'a' and 'c' trimmed -> "b" */
        {"abc", "b", "abc"},                   /* 'b' only in middle, not trimmed */
        {"aabbaa", "a", "bb"},                 /* trim leading/trailing 'a' */
        {"aabbaa", "ab", ""},                  /* all chars in set */
        {"  a b c  ", " ", "a b c"},           /* spaces only at ends, middle spaces kept */
        /* Complex sets */
        {"xyz123xyz", "xyz", "123"},
        {"**hello**", "*", "hello"},
        {"*hello*", "*", "hello"},
        {"**hello*", "*", "hello"},
        {"*hello**", "*", "hello"},
        {"*hello* ", "* ", "hello"},           /* set is "* " */
        {" \t\n hello \t\n ", " \t\n", "hello"},
        {"   ", " ", ""},
        {"   ", "", "   "},                    /* empty set -> copy */
        {"", "abc", ""},
        /* Mixed characters not in set */
        {"abca", "b", "abca"},                 /* 'b' not at ends */
        {"abca", "a", "bc"},                   /* trim 'a' at ends */
        {"abca", "abc", ""},                   /* all chars in set */
        {"abca", "bca", ""},                  /* 'a' at ends? Actually set {b,c,a}, all chars in set -> ""? Wait 'abca' contains only a,b,c, all in set, so should be "" */
        {"abca", "bc", "abca"},                /* 'a' not in set, so no trim */
        /* More edge cases: set contains repeated chars (no effect) */
        {"hello", "ll", "hello"},              /* 'l' is in middle, not at ends, so no trim */
        {"llhello", "l", "hello"},             /* trim leading 'l's */
        {"helloll", "l", "hello"},             /* trim trailing 'l's */
        {NULL, NULL, NULL} /* sentinel */
    };

    for (int i = 0; cases[i].s1 != NULL; i++)
    {
        const char *s1 = cases[i].s1;
        const char *set = cases[i].set;
        const char *exp = cases[i].expected;

        char *result = ft_strtrim(s1, set);

        /* Ensure result is not NULL (we assume allocation succeeds) */
        TEST_ASSERT(result != NULL, "ft_strtrim returned NULL");

        /* Compare with expected */
        char msg[256];
        snprintf(msg, sizeof(msg), "ft_strtrim('%s', '%s') mismatch, testno = %d, res = '%s'", s1, set, i, result);
        TEST_ASSERT(strcmp(result, exp) == 0, msg);

        /* Check that result is a new allocation (not same pointer) */
        TEST_ASSERT(result != s1, "ft_strtrim returned original pointer (should allocate)");

        free(result);
    }

    /* Additional test: verify that trimming does not remove characters from the middle */
    const char *s = "abcXYZdef";
    const char *set = "abc";
    char *r = ft_strtrim(s, set);
    TEST_ASSERT(r != NULL, "ft_strtrim returned NULL");
    TEST_ASSERT(strcmp(r, "XYZdef") == 0, "trim middle preservation failed"); /* 'abc' at start removed, 'def' remains */
    free(r);

    /* Set that includes characters that appear only in middle, should not affect */
    s = "hello world";
    set = "l";
    r = ft_strtrim(s, set);
    TEST_ASSERT(r != NULL, "ft_strtrim returned NULL");
    TEST_ASSERT(strcmp(r, "hello world") == 0, "middle char in set should not be trimmed");
    free(r);

    /* Test with set containing characters not in string */
    s = "hello";
    set = "xyz";
    r = ft_strtrim(s, set);
    TEST_ASSERT(r != NULL, "ft_strtrim returned NULL");
    TEST_ASSERT(strcmp(r, "hello") == 0, "set not present should return copy");
    free(r);
}

//ft_strmapi
// helpers for ft_strmapi tests
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
        {"abc", add_index, "ace"},
        {"abc", transform, "acc"},
        {"xyz", add_index, "xz|"},
        {NULL, NULL, NULL}
    };

    for (int i = 0; cases[i].s != NULL; i++)
    {
        const char *s = cases[i].s;
        char (*f)(unsigned int, char) = cases[i].f;
        const char *exp = cases[i].expected;

        char *result = ft_strmapi(s, f);

        /* Ensure result is not NULL */
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

//ft_strjoin
static void test_strjoin(void)
{
    printf("\n--- Testing ft_strjoin ---\n");

    struct {
        const char *s1;
        const char *s2;
        const char *expected;
    } cases[] = {
        {"", "", ""},
        {"", "hello", "hello"},
        {"hello", "", "hello"},
        {"hello", "world", "helloworld"},
        {"Hello, ", "World!", "Hello, World!"},
        {"abc", "def", "abcdef"},
        {"123", "456", "123456"},
        {"   ", "   ", "      "},
        {"", " ", " "},
        {" ", "", " "},
        {"abc", "123", "abc123"},
        {"xyz", "XYZ", "xyzXYZ"},
        {"\n", "\t", "\n\t"},
        {NULL, NULL, NULL}
    };

    for (int i = 0; cases[i].s1 != NULL; i++)
    {
        const char *s1 = cases[i].s1;
        const char *s2 = cases[i].s2;
        const char *exp = cases[i].expected;

        char *result = ft_strjoin(s1, s2);

        /* Ensure result is not NULL (we assume allocation succeeds) */
        TEST_ASSERT(result != NULL, "ft_strjoin returned NULL");

        /* Compare with expected */
        char msg[256];
        snprintf(msg, sizeof(msg), "ft_strjoin('%s', '%s') mismatch", s1, s2);
        TEST_ASSERT(strcmp(result, exp) == 0, msg);

        /* Ensure the result is a new allocation (not pointing to original strings) */
        TEST_ASSERT(result != s1 && result != s2,
                    "ft_strjoin returned original pointer (should allocate)");

        /* Check null-termination */
        size_t len = strlen(result);
        TEST_ASSERT(result[len] == '\0', "ft_strjoin missing null terminator");

        /* Ensure total length matches expected */
        size_t expected_len = strlen(s1) + strlen(s2);
        TEST_ASSERT(strlen(result) == expected_len,
                    "ft_strjoin length mismatch");

        free(result);
    }

    /* Additional test: s1 and s2 are the same string? Should still work */
    const char *same = "hello";
    char *r = ft_strjoin(same, same);
    TEST_ASSERT(r != NULL, "ft_strjoin returned NULL");
    TEST_ASSERT(strcmp(r, "hellohello") == 0,
                "ft_strjoin with same string failed");
    free(r);

    /* Test with very long strings (but limited to avoid excessive time) */
    char long_s1[256], long_s2[256];
    memset(long_s1, 'A', sizeof(long_s1) - 1);
    long_s1[sizeof(long_s1) - 1] = '\0';
    memset(long_s2, 'B', sizeof(long_s2) - 1);
    long_s2[sizeof(long_s2) - 1] = '\0';
    char expected_long[512];
    snprintf(expected_long, sizeof(expected_long), "%s%s", long_s1, long_s2);

    r = ft_strjoin(long_s1, long_s2);
    TEST_ASSERT(r != NULL, "ft_strjoin returned NULL for long strings");
    TEST_ASSERT(strcmp(r, expected_long) == 0,
                "ft_strjoin long strings mismatch");
    TEST_ASSERT(strlen(r) == (strlen(long_s1) + strlen(long_s2)),
                "ft_strjoin long strings length mismatch");
    free(r);
}

// ft_striteri
// helpers for ft_striteri
static void to_upper_at_index(unsigned int i, char *c)
{
    (void)i;
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32;
}

static void add_index_to_char(unsigned int i, char *c)
{
    *c = *c + i;
}

static void alternate_case(unsigned int i, char *c)
{
    if (i % 2 == 0)
        *c = *c + 1;   /* shift every even index char */
    else
        *c = *c - 1;   /* shift every odd index char */
}

static void test_striteri(void)
{
    printf("\n--- Testing ft_striteri ---\n");

    struct {
        char *s;
        void (*f)(unsigned int, char *);
        const char *expected;
    } cases[] = {
        {(char *)"", to_upper_at_index, ""},
        {(char *)"hello", to_upper_at_index, "HELLO"},
        {(char *)"abc", add_index_to_char, "ace"},
        {(char *)"abc", alternate_case, "bad"},
        {NULL, NULL, NULL} /* sentinel */
    };

    for (int i = 0; cases[i].s != NULL; i++)
    {
        char *copy = strdup(cases[i].s);
        if (!copy)
        {
            TEST_ASSERT(0, "strdup failed in test");
            continue;
        }

        /* Apply ft_striteri */
        ft_striteri(copy, cases[i].f);

        /* Check result */
        char msg[256];
        snprintf(msg, sizeof(msg), "ft_striteri mismatch for '%s'", cases[i].s);
        TEST_ASSERT(strcmp(copy, cases[i].expected) == 0, msg);

        free(copy);
    }
}

//ft_split
static void test_split(void)
{
    printf("\n--- Testing ft_split ---\n");

    struct {
        const char *s;
        char c;
        const char **expected;
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
        {NULL, 0, NULL}
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

// t_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd
/* create a unique temporary file and return its file descriptor.
   The filename is stored in 'name' (must be at least 20 bytes). */
static int create_temp_file(char *name)
{
    static const char template[] = "/tmp/libft_test_XXXXXX";
    strcpy(name, template);
    int fd = mkstemp(name);
    if (fd == -1)
    {
        perror("mkstemp");
        exit(EXIT_FAILURE);
    }
    return (fd);
}

//read entire content of a file into a newly allocated string.
static char *read_temp_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (NULL);
    }
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1)
    {
        perror("lseek");
        close(fd);
        return (NULL);
    }
    lseek(fd, 0, SEEK_SET);
    char *buf = malloc(size + 1);
    if (!buf)
    {
        close(fd);
        return (NULL);
    }
    ssize_t bytes = read(fd, buf, size);
    if (bytes != size)
    {
        free(buf);
        close(fd);
        return (NULL);
    }
    buf[size] = '\0';
    close(fd);
    unlink(filename);
    return (buf);
}

static void test_putchar_fd(void)
{
    printf("\n--- Testing ft_putchar_fd ---\n");
    char filename[64];
    int fd = create_temp_file(filename);

    /* Write a single character */
    ft_putchar_fd('A', fd);
    close(fd);

    char *content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "A") == 0, "ft_putchar_fd('A') failed");

    /* Test newline and other chars */
    fd = create_temp_file(filename);
    ft_putchar_fd('\n', fd);
    ft_putchar_fd('B', fd);
    ft_putchar_fd('\0', fd);
    ft_putchar_fd('C', fd);
    close(fd);

    content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    size_t expected_len = 2; /* newline, 'B', '\0', 'C' */
    TEST_ASSERT(strlen(content) == expected_len, "ft_putchar_fd length mismatch");
    TEST_ASSERT(content[0] == '\n' && content[1] == 'B' && content[2] == '\0' && content[3] == 'C',
                "ft_putchar_fd multi-char failed");
    free(content);
}

static void test_putstr_fd(void)
{
    printf("\n--- Testing ft_putstr_fd ---\n");
    char filename[64];
    int fd = create_temp_file(filename);

    /* Empty string */
    ft_putstr_fd("", fd);
    close(fd);
    char *content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "") == 0, "ft_putstr_fd empty string failed");
    free(content);

    /* Normal string */
    fd = create_temp_file(filename);
    ft_putstr_fd("Hello, World!", fd);
    close(fd);
    content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "Hello, World!") == 0,
                "ft_putstr_fd 'Hello, World!' failed");
    free(content);

    /* String with newline and null byte  */
    fd = create_temp_file(filename);
    ft_putstr_fd("abc\0def", fd);  /* writes only "abc" */
    close(fd);
    content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "abc") == 0,
                "ft_putstr_fd with embedded null failed");
    free(content);

    /* Long string */
    char long_str[512];
    memset(long_str, 'X', sizeof(long_str) - 1);
    long_str[sizeof(long_str) - 1] = '\0';
    fd = create_temp_file(filename);
    ft_putstr_fd(long_str, fd);
    close(fd);
    content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, long_str) == 0,
                "ft_putstr_fd long string failed");
    free(content);
}

static void test_putendl_fd(void)
{
    printf("\n--- Testing ft_putendl_fd ---\n");
    char filename[64];
    int fd = create_temp_file(filename);

    /* Empty string */
    ft_putendl_fd("", fd);
    close(fd);
    char *content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "\n") == 0,
                "ft_putendl_fd empty string failed (should output newline)");
    free(content);

    /* Normal string */
    fd = create_temp_file(filename);
    ft_putendl_fd("Hello", fd);
    close(fd);
    content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "Hello\n") == 0,
                "ft_putendl_fd 'Hello' failed");
    free(content);

    /* String with newline already (should output extra newline) */
    fd = create_temp_file(filename);
    ft_putendl_fd("Hi\n", fd);
    close(fd);
    content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "Hi\n\n") == 0,
                "ft_putendl_fd with existing newline failed");
    free(content);
}

static void test_putnbr_fd(void)
{
    printf("\n--- Testing ft_putnbr_fd ---\n");
    char filename[64];
    int fd;

    /* Test zero */
    fd = create_temp_file(filename);
    ft_putnbr_fd(0, fd);
    close(fd);
    char *content = read_temp_file(filename);
    TEST_ASSERT(content != NULL, "read_temp_file failed");
    TEST_ASSERT(strcmp(content, "0") == 0,
                "ft_putnbr_fd(0) failed");
    free(content);

    /* Positive numbers */
    int nums[] = {1, 42, 1234567, 2147483647};
    for (size_t i = 0; i < sizeof(nums) / sizeof(nums[0]); i++)
    {
        fd = create_temp_file(filename);
        ft_putnbr_fd(nums[i], fd);
        close(fd);
        content = read_temp_file(filename);
        TEST_ASSERT(content != NULL, "read_temp_file failed");
        char expected[32];
        snprintf(expected, sizeof(expected), "%d", nums[i]);
        TEST_ASSERT(strcmp(content, expected) == 0,
                    "ft_putnbr_fd positive mismatch");
        free(content);
    }

    /* Negative numbers */
    int neg_nums[] = {-1, -42, -1234567, -2147483648};
    for (size_t i = 0; i < sizeof(neg_nums) / sizeof(neg_nums[0]); i++)
    {
        fd = create_temp_file(filename);
        ft_putnbr_fd(neg_nums[i], fd);
        close(fd);
        content = read_temp_file(filename);
        TEST_ASSERT(content != NULL, "read_temp_file failed");
        char expected[32];
        snprintf(expected, sizeof(expected), "%d", neg_nums[i]);
        TEST_ASSERT(strcmp(content, expected) == 0,
                    "ft_putnbr_fd negative mismatch");
        free(content);
    }
}

// ft_itoa
static void test_itoa(void)
{
    printf("\n--- Testing ft_itoa ---\n");

    struct {
        int n;
        const char *expected;
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
    test_ctype_macros();
    test_tolower_toupper();
    test_atoi();
    test_bzero();
    test_calloc();
    test_memchr();
    test_memcmp();
    test_memcpy();
    test_memmove();
    test_memset();
    test_strlen();
    test_strdup();
    test_strchr();
    test_strlcpy();
    test_strlcat();
    test_strncmp();
    test_strnstr();
    test_strrchr();
    test_split();
    test_itoa();
    test_strmapi();
    test_putchar_fd();
    test_putstr_fd();
    test_putendl_fd();
    test_putnbr_fd();
    test_striteri();
    test_strtrim();
    test_strjoin();
    test_substr();
    print_summary();
    return (g_failed_tests != 0);
}
