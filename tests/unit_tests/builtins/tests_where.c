/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for where
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_where, .init = init_tests, .fini = end_tests);

Test(builtin_where, basic_where) {
    // Note: bash's "which --all" is equivalent to "where"
    // Note 2: use bash's which here as TCSH is uses paths not in PATH
    char *expected_output = capture_stdout("bash -c 'which --all ls'");
    char *args[] = {"where", "ls", NULL};
    builtin_where(args, data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "BASIC WHERE | Expected to display all the locations of a given command.");
}

Test(builtin_where, too_few_args_where) {
    char *args[] = {"where", NULL};
    int exit_value = builtin_where(args, data);

    cr_assert_stderr_eq_str("where: Too few arguments.\n",
        "TOO FEW ARGS WHERE | Expected the valid error message.");
    cr_assert_eq(exit_value, 1,
        "TOO FEW ARGS WHERE | Expected for return value : 1");
}

Test(builtin_where, where_with_builtin) {
    char *args[] = {"where", "cd", NULL};
    int exit_value = builtin_where(args, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("cd is a shell built-in\n",
        "WHERE WITH BUILTIN | Expected the valid error message.");
    cr_assert_eq(exit_value, 0,
        "WHERE WITH BUILTIN | Expected for return value : 0");
}

Test(builtin_where, wrong_builtin) {
    char *args[] = {"where", "foobar", NULL};
    int exit_value = builtin_where(args, data);

    cr_assert_eq(exit_value, 1,
        "WRONG WHERE | Expected for return value : 1");
}
