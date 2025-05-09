/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for str_join
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(str_join, .init = init_tests, .fini = end_tests);

Test(str_join, basic_str_join) {
    char *str1 = "test1";
    char *str2 = "test2";
    char *result = sh_strjoin(str1, str2);

    cr_assert_str_eq(result, "test1test2",
        "BASIC STR JOIN | Excepted as result : 'str1+str2'.");
}
