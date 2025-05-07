/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for exec
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_exec, .init = init_tests, .fini = end_tests);

Test(builtin_exec, verify_exec_is_valid) {
    char *expected_output = capture_stdout("exec ls");
    char *args[] = {"exec", "ls", NULL};
    int exit_value = builtin_exec(args, data);

    cr_assert_stdout_eq_str(expected_output,
        "VALID EXEC | Expected the valid exec output.");
    cr_assert_eq(exit_value, 0,
        "VALID EXEC | Expected for return value : 0");
}

Test(builtin_exec, no_args_exec) {
    char *args[] = {"exec", NULL};
    int exit_value = builtin_exec(args, data);

    cr_assert_eq(exit_value, 0,
        "NO ARGS EXEC | Expected for return value : 0");
}

Test(builtin_exec, wrong_command) {
    char *args[] = {"exec", "cd", NULL};
    int exit_value = builtin_exec(args, data);

    cr_assert_eq(exit_value, 127,
        "WRONG COMMAND EXEC | Expected for return value : 127");
}
