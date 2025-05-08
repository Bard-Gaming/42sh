/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for str_is_num
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(str_is_num, .init = init_tests, .fini = end_tests);

Test(str_is_num, valid_num) {
    int result = sh_strisnum("42");

    cr_assert_eq(result, 1,
        "VALID NUM | expected as result : true");
}

Test(str_is_num, invalid_num) {
    int result = sh_strisnum("test");

    cr_assert_eq(result, 0,
        "INVALID NUM | expected as result : false");
}
