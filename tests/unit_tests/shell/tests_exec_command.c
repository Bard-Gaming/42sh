/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for exec_command
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>
#include <sys/wait.h>


extern sh_data_t *data;


TestSuite(exec_command, .init = init_tests, .fini = end_tests);

Test(exec_command, signal_exec_command) {
    pid_t pid = fork();
    int status;
    if (pid == 0) {
        raise(SIGFPE);
    }
    waitpid(pid, &status, 0);
    char *args[] = {"./tests/unit_tests/signal_exec", NULL};
    int exit_value = shell_exec_command(args, data);

    cr_assert_eq(exit_value, status,
        "SIGNAL EXEC COMMAND | Expected to return same exit status as signal SIGFPE.");
}
