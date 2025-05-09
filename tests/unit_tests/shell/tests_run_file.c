/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for run_file
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>


extern sh_data_t *data;


TestSuite(run_file, .init = init_tests, .fini = end_tests);

Test(run_file, basic_run_file) {
    system("echo 'echo test' > test_file");
    char *args[] = { NULL };
    int exit_value = shell_run_file(data, "test_file", args);
    system("rm test_file");

    fflush(stdout);
    cr_assert_stdout_eq_str("test\n",
        "BASIC RUN FILE | Expected the right output corresponding to the command in the file.");
    cr_assert_eq(exit_value, 0,
        "BASIC RUN FILE | Expected for return value : 0");
}

Test(run_file, wrong_run_file) {
    char *args[] = { NULL };
    int exit_value = shell_run_file(data, "wrong_file", args);

    cr_assert_eq(exit_value, -1,
        "WRONG RUN FILE | Expected for return value : -1");
}
