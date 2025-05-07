/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for env
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_env, .init = init_tests, .fini = end_tests);

// Test(builtin_env, verify_env_is_valid) {
//     char *expected_output = capture_stdout("env");
//     char *args[] = {"env", NULL};
//     int exit_value = builtin_env(args, data);

//     cr_assert_stdout_eq_str(expected_output,
//         "VALID ENV | Expected the valids env variables.");
//     cr_assert_eq(exit_value, 0,
//         "VALID ENV | Expected for return value : 0");
// }

Test(builtin_env, too_many_args) {
    char *args[] = {"env", "arg", NULL};
    int exit_value = builtin_env(args, data);

    cr_assert_stderr_eq_str("env: Too many arguments.\n",
        "TOO MANY ARGS ENV | Expected for error message : 'env: Too many arguments.'");
    cr_assert_eq(exit_value, 1,
        "TOO MANY ARGS ENV | Expected for return value : 1");
}
