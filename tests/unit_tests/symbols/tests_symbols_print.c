/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for symbols_print
** symbols
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/symbols.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(symbols_print, .init = init_tests, .fini = end_tests);

Test(symbols_print, simple_symbols_print) {
    sh_symbols_t *table = malloc(sizeof(sh_symbols_t));
    memset(table, 0, sizeof(sh_symbols_t));
    char *name = strdup("name");
    char *value = strdup("test");
    sh_symbols_set(table, name, value);
    sh_symbols_print(table, "=");

    fflush(stdout);
    cr_assert_stdout_eq_str("name=test\n",
        "SIMPLE SYMBOLS PRINT | Expected output : 'name=value'.");
}
