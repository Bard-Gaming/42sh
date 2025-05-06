/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for alias
** builtin
*/

#include <42sh/builtins.h>
#include <42sh/data.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_alias, .init = init_tests, .fini = end_tests);

Test(builtin_alias, print_all_alias) {
    char *args1[] = {"alias", "quoi", "echo", "feur", NULL};
    int exit_value = builtin_alias(args1, data);
    char *args2[] = {"alias", NULL};
    builtin_alias(args2, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("quoi\techo feur\n",
        "PRINT ALL ALIAS | Expected this alias : 'quoi  echo feur'");
    cr_assert_eq(exit_value, 0,
        "PRINT ALL ALIAS | Expected for return value : 0");
}

Test(builtin_alias, print_one_alias) {
    char *args1[] = {"alias", "quoi", "echo", "feur", NULL};
    int exit_value = builtin_alias(args1, data);
    char *args2[] = {"alias", "quoi", NULL};
    builtin_alias(args2, data);

    fflush(stdout);
    cr_assert_stdout_eq_str("echo feur\n",
        "PRINT ONE ALIAS | Expected this alias : 'echo feur'");
    cr_assert_eq(exit_value, 0,
        "PRINT ONE ALIAS | Expected for return value : 0");
}
