/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for foreach_loop
** shell
*/

#include "../../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(foreach_loop, .init = init_tests, .fini = end_tests);

Test(foreach_loop, basic_foreach_loop) {
    shell_system("foreach x (a b c); echo $x; end", data);

    cr_assert_stdout_eq_str("a\nb\nc\n",
        "BASIC FOREACH LOOP | Expected to print the 3 elements.");
}

Test(foreach_loop, wrong_var_name) {
    shell_system("foreach 0 (a b c); echo $0; end", data);

    cr_assert_stderr_eq_str("foreach: Variable name must begin with a letter.\n",
        "WRONG VAR NAME FOREACH LOOP | Expected right error message : 'foreach: Variable name must begin with a letter.'");
}

Test(foreach_loop, too_much_var_name) {
    shell_system("foreach `echo 'a' 'b'` (a b c); echo $x; end", data);

    cr_assert_stderr_eq_str("foreach: Variable name must be a single argument.\n",
        "TOO MUCH VAR NAME FOREACH LOOP | Expected right error message : 'foreach: Variable name must be a single argument.'");
}
