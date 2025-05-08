/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for set
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_set, .init = init_tests, .fini = end_tests);

Test(builtin_set, single_var_set) {
    char *args1[] = {"set", "test", NULL};
    builtin_set(args1, data);
    char *args2[] = {"set", NULL};
    int exit_value = builtin_set(args2, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("test\t\n",
        "SINGLE VAR SET | Expected to display all local vars.");
    cr_assert_eq(exit_value, 0,
        "SINGLE VAR SET | Expected for return value : 0");
}

Test(builtin_set, couple1_var_set) {
    char *args1[] = {"set", "test", "=", "caca", NULL};
    builtin_set(args1, data);
    char *args2[] = {"set", NULL};
    int exit_value = builtin_set(args2, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("test\tcaca\n",
        "COUPLE 1 VAR SET | Expected to display all local vars.");
    cr_assert_eq(exit_value, 0,
        "COUPLE 1 VAR SET | Expected for return value : 0");
}

Test(builtin_set, couple2_var_set) {
    char arg_command[] = "test=caca";
    char *args1[] = {"set", arg_command, NULL};
    builtin_set(args1, data);
    char *args2[] = {"set", NULL};
    int exit_value = builtin_set(args2, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("test\tcaca\n",
        "COUPLE 2 VAR SET | Expected to display all local vars.");
    cr_assert_eq(exit_value, 0,
        "COUPLE 2 VAR SET | Expected for return value : 0");
}

Test(builtin_set, wrong_var_set) {
    char *args1[] = {"set", "0test", NULL};
    int exit_value = builtin_set(args1, data);

    cr_assert_eq(exit_value, 1,
        "WRONG VAR SET | Expected for return value : 1");
}
