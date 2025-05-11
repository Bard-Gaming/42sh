/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for print_columns
** io
*/

#include "../tests.h"
#include <42sh/io.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(print_columns, .init = init_tests, .fini = end_tests);

Test(print_columns, basic_print_columns) {
    char *args[] = { "test1", "test2", "test3", "test4", NULL };
    sh_print_columns(args);

    fflush(stdout);
    cr_assert_stdout_neq_str("",
        "BASIC PRINT COLUMNS | Expected not void output.");
}
