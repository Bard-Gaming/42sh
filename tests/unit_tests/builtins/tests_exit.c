/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for exit
** builtin
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_exit, .init = init_tests, .fini = end_tests);

Test(builtin_exit, basic_exit) {
    char *args[] = {"exit", NULL};
    int exit_value = builtin_exit(args, data);

    cr_assert_eq(exit_value, data->exit_status,
        "BASIC EXIT | Expected right return value.");
}

Test(builtin_exit, specified_exit_status) {
    char *args[] = {"exit", "42", NULL};
    int exit_value = builtin_exit(args, data);

    cr_assert_eq(exit_value, 42,
        "WRONG EXIT | Expected for return value : 42.");
}

Test(builtin_exit, wrong_exit) {
    char *args[] = {"exit", "wrong", NULL};
    int exit_value = builtin_exit(args, data);

    cr_assert_eq(exit_value, 84,
        "WRONG EXIT | Expected for return value : 84.");
}
