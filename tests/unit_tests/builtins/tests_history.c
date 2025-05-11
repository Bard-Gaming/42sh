/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for history
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/shell.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_history, .init = init_tests, .fini = end_tests);

Test(builtin_history, basic_history) {
    shell_init(data);
    char *args[] = { "history", NULL };
    int exit_value = builtin_history(args, data);

    cr_assert_eq(exit_value, 0,
        "BASIC HISTORY | Expected for return value : 0");
}

Test(builtin_history, too_many_args_history) {
    shell_init(data);
    char *args[] = { "history", "test1", "test2", NULL };
    int exit_value = builtin_history(args, data);

    cr_assert_stderr_eq_str("history: Too many arguments.\n",
        "TOO MANY ARGS HISTORY | Expected this error message : 'history: Too many arguments.'");
    cr_assert_eq(exit_value, 1,
        "TOO MANY ARGS HISTORY | Expected for return value : 1");
}

Test(builtin_history, badly_formed_args_history) {
    shell_init(data);
    char *args[] = { "history", "test", NULL };
    int exit_value = builtin_history(args, data);

    cr_assert_stderr_eq_str("history: Badly formed number.\n",
        "BADLY FORMED ARGS HISTORY | Expected this error message : 'history: Badly formed number.'");
    cr_assert_eq(exit_value, 1,
        "BADLY FORMED ARGS HISTORY | Expected for return value : 1");
}
