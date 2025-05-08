/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for repeat
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_repeat, .init = init_tests, .fini = end_tests);

Test(builtin_repeat, basic_repeat) {
    char *expected_output = capture_stdout("ls");
    char *args[] = {"repeat", "1", "ls", NULL};
    int exit_value = builtin_repeat(args, data);

    cr_assert_stdout_eq_str(expected_output,
        "BASIC REPEAT | Expected the valid repeat output.");
    cr_assert_eq(exit_value, 0,
        "BASIC REPEAT | Expected for return value : 0");
}

Test(builtin_repeat, too_few_args_repeat) {
    char *args[] = {"repeat", NULL};
    int exit_value = builtin_repeat(args, data);

    cr_assert_stderr_eq_str("repeat: Too few arguments.\n",
        "TOO FEW ARGS REPEAT | Expected the valid error message.");
    cr_assert_eq(exit_value, 1,
        "TOO FEW ARGS REPEAT | Expected for return value : 1");
}

Test(builtin_repeat, wrong_args_repeat) {
    char *args[] = {"repeat", "wrong", "ls", NULL};
    int exit_value = builtin_repeat(args, data);

    cr_assert_stderr_eq_str("repeat: Badly formed number.\n",
        "WRONG ARGS REPEAT | Expected the valid error message.");
    cr_assert_eq(exit_value, 1,
        "WRONG ARGS REPEAT | Expected for return value : 1");
}
