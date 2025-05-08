/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for str_append
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(str_append, .init = init_tests, .fini = end_tests);

Test(str_append, valid_append) {
    char *dest = strdup("test1");
    sh_strappend(&dest, "test2");

    cr_assert_str_eq(dest, "test1test2",
        "VALID APPEND | expected this string : 'arg1+arg2'");
}
