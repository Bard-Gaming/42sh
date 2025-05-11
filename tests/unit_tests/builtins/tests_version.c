/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for version
** builtin
*/

#include "../tests.h"
#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/shell.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_version, .init = init_tests, .fini = end_tests);

Test(builtin_version, basic_version) {
    shell_init(data);
    char *args[] = { "version", NULL };
    int exit_value = builtin_version(args, data);

    fflush(stdout);
    cr_assert_stdout_neq_str("",
        "BASIC VERSION | Expected not void output.");
    cr_assert_eq(exit_value, 0,
        "BASIC VERSION | Expected for return value : 0");
}
