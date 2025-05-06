/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for unalias
** builtin
*/

#include <42sh/builtins.h>
#include <42sh/data.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_unalias, .init = init_tests, .fini = end_tests);

Test(builtin_unalias, remove_single_alias) {
    char *args1[] = {"alias", "quoi", "echo", "feur", NULL};
    builtin_alias(args1, data);
    char *args2[] = {"unalias", "quoi", NULL};
    builtin_unalias(args2, data);
    char *args3[] = {"alias", NULL};
    builtin_alias(args3, data);

    fflush(stdout);
    cr_assert_stdout_neq_str("quoi\techo feur\n",
        "REMOVE SINGLE ALIAS | Expected to remove the only existant alias.");
}

Test(builtin_alias, too_few_args_unalias) {
    char *args[] = {"unalias", NULL};
    int exit_value = builtin_unalias(args, data);

    fflush(stdout);
    cr_assert_stderr_eq_str("unalias: Too few arguments.\n",
        "TOO FEW ARGS UNALIAS | Expected for error message : 'unalias: Too few arguments.'");
    cr_assert_eq(exit_value, 1,
        "TOO FEW ARGS UNALIAS | Expected for return value : 1");
}
