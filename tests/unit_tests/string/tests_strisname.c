/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for str_is_name
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(str_is_name, .init = init_tests, .fini = end_tests);

Test(str_is_name, invalid_start) {
    int exit_value = sh_strisname("0test", "test");
    char *error_message = "test: Variable name must begin with a letter.\n";

    cr_assert_stderr_eq_str(error_message,
        "INVALID START STRING | Expected error message : 'test: Variable name must begin with a letter.'");
    cr_assert_eq(exit_value, 0,
        "INVALID START STRING | Expected for return value : 0");
}

Test(str_is_name, illegal_char) {
    int exit_value = sh_strisname("te.st", "test");
    char *error_message = "test: Variable name must contain alphanumeric characters.\n";

    cr_assert_stderr_eq_str(error_message,
        "ILLEGAL CHAR STRING | Expected error message : 'test: Variable name must contain alphanumeric characters.'");
    cr_assert_eq(exit_value, 0,
        "ILLEGAL CHAR STRING | Expected for return value : 0");
}

Test(str_is_name, valid_name) {
    int exit_value = sh_strisname("test", "test");

    cr_assert_eq(exit_value, 1,
        "VALID NAME STRING | Expected for return value : 1");
}
