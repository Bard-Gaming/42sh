/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for unset
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_unset, .init = init_tests, .fini = end_tests);

Test(builtin_unset, remove_single_var_unset) {
    char *args1[] = {"set", "test", NULL};
    builtin_set(args1, data);
    char *args2[] = {"unset", "test", NULL};
    builtin_unset(args2, data);
    char *args3[] = {"set", NULL};
    builtin_set(args3, data);

    fflush(stdout);
    cr_assert_stdout_neq_str("test\t\n",
        "REMOVE SINGLE VAR UNSET | Expected to remove the only existant local var.");
}

Test(builtin_unset, too_few_args_unset) {
    char *args[] = {"unset", NULL};
    int exit_value = builtin_unset(args, data);

    fflush(stdout);
    cr_assert_stderr_eq_str("unset: Too few arguments.\n",
        "TOO FEW ARGS UNSET | Expected for error message : 'unset: Too few arguments.'");
    cr_assert_eq(exit_value, 1,
        "TOO FEW ARGS UNSET | Expected for return value : 1");
}
