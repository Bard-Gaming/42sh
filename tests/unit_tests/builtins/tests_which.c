/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for which
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_which, .init = init_tests, .fini = end_tests);

Test(builtin_which, basic_which) {
    char *expected_output = capture_stdout("tcsh -c 'which ls'");
    char *args[] = {"which", "ls", NULL};
    builtin_which(args, data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "BASIC WHICH | Expected to display same as official which command.");
}

Test(builtin_which, too_few_args_which) {
    char *args[] = {"which", NULL};
    int exit_value = builtin_which(args, data);

    cr_assert_stderr_eq_str("which: Too few arguments.\n",
        "TOO FEW ARGS WHICH | Expected the valid error message.");
    cr_assert_eq(exit_value, 1,
        "TOO FEW ARGS WHICH | Expected for return value : 1");
}

Test(builtin_which, which_with_builtin) {
    char *args[] = {"which", "cd", NULL};
    int exit_value = builtin_which(args, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("cd: shell built-in command.\n",
        "WHICH WITH BUILTIN | Expected the valid error message.");
    cr_assert_eq(exit_value, 0,
        "WHICH WITH BUILTIN | Expected for return value : 0");
}

Test(builtin_which, wrong_builtin) {
    char *args[] = {"which", "foobar", NULL};
    int exit_value = builtin_which(args, data);

    cr_assert_eq(exit_value, 1,
        "WRONG WHICH | Expected for return value : 1");
}
