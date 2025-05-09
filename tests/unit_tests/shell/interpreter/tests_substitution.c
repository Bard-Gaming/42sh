/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for substitution
** shell
*/

#include "../../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>


extern sh_data_t *data;


TestSuite(shell_substitution, .init = init_tests, .fini = end_tests);

Test(shell_substitution, basic_substitution) {
    shell_system("echo \"a`echo b; echo c`d\"", data);

    fflush(stdout);
    cr_assert_stdout_eq_str("ab cd\n",
        "BASIC SUBSTITUTION | Expected to formating the command with correct rules.");
}
