/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for itoa
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(itoa, .init = init_tests, .fini = end_tests);

Test(itoa, basic_use) {
    char result[10];
    sh_itoa(result, 42);

    cr_assert_str_eq(result, "42",
        "BASIC USE ITOA | Excepted working for basic number like 42.");
}

Test(itoa, negative_value) {
    char result[10];
    sh_itoa(result, -42);

    cr_assert_str_eq(result, "-42",
        "NEGATIVE VALUE ITOA | Excepted working for negative number like -42.");
}

Test(itoa, zero_value) {
    char result[10];
    sh_itoa(result, 0);

    cr_assert_str_eq(result, "0",
        "ZERO VALUE ITOA | Excepted working for zero value.");
}
