/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for setenv
** builtin
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_setenv, .init = init_tests, .fini = end_tests);

Test(builtin_setenv, basic_setenv) {
    char *args[] = {"setenv", "test", "test", NULL};
    int exit_value = builtin_setenv(args, data);
    const char *var = sh_data_getvar(data, "test");

    cr_assert_str_eq(var, "test",
        "BASIC SETENV | Expected the added var in the environment.");
    cr_assert_eq(exit_value, 0,
        "BASIC SETENV | Expected for return value : 0");
}

Test(builtin_setenv, too_many_args_setenv) {
    char *args[] = {"setenv", "test", "test", "test", NULL};
    int exit_value = builtin_setenv(args, data);

    cr_assert_stderr_eq_str("setenv: Too many arguments.\n",
        "TOO MANY ARGS SETENV | Expected for error message : 'setenv: Too many arguments.'");
    cr_assert_eq(exit_value, 1,
        "TOO MANY ARGS SETENV | Expected for return value : 1");
}

Test(builtin_setenv, wrong_arg_setenv) {
    char *args[] = {"setenv", "0test", "test", NULL};
    int exit_value = builtin_setenv(args, data);

    cr_assert_eq(exit_value, 1,
        "WRONG ARG SETENV | Expected for return value : 1");
}
