/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for shell_system
** shell
*/

#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(shell_system, .init = init_tests, .fini = end_tests);

Test(shell_system, valid_command) {
    char *expected_output = capture_stdout("whoami");
    shell_init(data);
    shell_system("whoami", data);

    cr_assert_stdout_eq_str(expected_output,
        "VALID SHELL SYSTEM | Expected working for this basic command : 'ls'");
}

Test(shell_system, invalid_command) {
    char *expected_output = capture_stdout("cd unknow_file");
    shell_init(data);
    shell_system("cd unknow_file", data);

    cr_assert_stdout_eq_str(expected_output,
        "INVALID SHELL SYSTEM | Expected error message for this command : 'cd unknow_file'");
}
