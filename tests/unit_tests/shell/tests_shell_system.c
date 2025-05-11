/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for shell_system
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
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
    const char *expected_error = "Invalid null command.\n";
    shell_init(data);
    shell_system("| cat", data);

    cr_assert_stderr_eq_str(expected_error,
        "INVALID SHELL SYSTEM | Expected \"Invalid null command.\" error");
}

Test(shell_system, null_command) {
    const char *expected_output = "";

    shell_init(data);
    shell_system("\n\t   \t\n", data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "NULL COMMAND SHELL SYSTEM | Expected no output");
}

Test(shell_system, command_logical_operators) {
    const char *expected_output =
        "hi\n"
        "bye\n"
        "failure\n";

    shell_init(data);
    shell_system(
        "echo hi && echo bye || echo error\n"
        "ls bob && echo hi || echo failure\n",
        data
    );

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "LOGICAL OPERATORS SHELL SYSTEM | Expected:\nhi\nbye\n");
}

Test(shell_system, command_pipes) {
    const char *expected_output =
        "bye\n"
        "hi\n";

    shell_init(data);
    shell_system("(echo hi; echo bye) | cat | sort | cat", data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "PIPES SHELL SYSTEM | Expected:\nbye\nhi\n");
}

Test(shell_system, if_statement) {
    const char *expected_output =
        "hi\n";

    shell_init(data);
    shell_system(
        "if ( hi ) then\n"
        "    echo hi\n"
        "endif", data
    );

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "IF STMNT SHELL SYSTEM | Expected:\nhi\n");
}

Test(shell_system, if_statement_else) {
    const char *expected_output =
        "bye\n";

    shell_init(data);
    shell_system(
        "if ( a == b ) then\n"
        "    echo hi\n"
        "else if ({ false }) then\n"
        "    echo hi\n"
        "else\n"
        "    echo bye\n"
        "endif", data
    );

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "IF STMNT ELSE SHELL SYSTEM | Expected:\nhi\n");
}

Test(shell_system, complex_command) {
    const char *expected_output =
        "bob\n"
        "hi\n"
        "hi\n";

    shell_init(data);
    shell_system("exit | echo \"bob\"; (cd ..; echo `echo hi`) && echo 'hi'", data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "COMPLEX COMMAND SHELL SYSTEM | Expected:\nbob\nhi\nhi\n");
}

Test(shell_system, inline_if_statement) {
    const char *expected_output =
        "hihihi\n";

    shell_init(data);
    shell_system("if (a == a) echo hihihi", data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "INLINE IF STMNT SHELL SYSTEM | Expected:\nhihihi\n");
}

Test(shell_system, ending_else_statement) {
    const char *expected_output = "";

    shell_init(data);
    shell_system(
        "if (a == b) then\n"
        "    echo hihihi\n"
        "else",
        data
    );

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "IF STMNT ELSE END SHELL SYSTEM | Expected no output");
}
