/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for autocomplete_func
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <unistd.h>
#include <pwd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(shell_autocomplete, .init = init_tests, .fini = end_tests);

Test(shell_autocomplete, echo_autocomplete) {
    shell_init(data);
    char *output = shell_autocomplete("ech");

    cr_assert_str_eq(output, "echo ",
        "ECHO AUTOCOMPLETE | Expected to have 'echo' in output for 'ech' in input.");
}

Test(shell_autocomplete, alias_autocomplete) {
    shell_init(data);
    shell_system("alias zorbu 'echo zurbu'", data);
    shell_system("alias test 'echo test'", data);
    char *output = shell_autocomplete("zorb");

    cr_assert_str_eq(output, "zorbu ",
        "ALIAS AUTOCOMPLETE | Expected to change the input for the input alias.");
}

Test(shell_autocomplete, multiple_match_autocomplete) {
    shell_init(data);
    char *output = shell_autocomplete("l");

    cr_assert_str_eq(output, "l",
        "MULTIPLE MATCH AUTOCOMPLETE | Expected to not change the input in case of multiple match.");
}

Test(shell_autocomplete, null_autocomplete) {
    shell_init(data);
    char *output = shell_autocomplete(NULL);

    cr_assert_null(output,
        "NULL AUTOCOMPLETE | Expected to have NULL for output.");
}

Test(shell_autocomplete, unknow_autocomplete) {
    shell_init(data);
    char *output = shell_autocomplete("zenhunhezt");

    cr_assert_null(output,
        "UNKNOW AUTOCOMPLETE | Expected to have NULL for output.");
}

/* Test(shell_autocomplete, autocomplete_long) { */
/*     shell_init(data); */
/*     shell_system("alias test1 'echo test1'", data); */
/*     shell_system("alias test2 'echo test2'", data); */
/*     shell_autocomplete_long("test"); */

/*     fflush(stdout); */
/*     cr_assert_stdout_eq_str("test2 test1 test\n", */
/*         "CACA| Expected to change the input for the input alias."); */
/* } */
