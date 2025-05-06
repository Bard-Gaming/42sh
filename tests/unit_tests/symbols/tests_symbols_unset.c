/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for symbols_unset
** symbols
*/

#include <42sh/data.h>
#include <42sh/symbols.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(symbols_unset, .init = init_tests, .fini = end_tests);


Test(symbols_unset, simple_symbols_unset) {
    sh_symbols_t *table = malloc(sizeof(sh_symbols_t));
    char *name = strdup("name");
    char *value = strdup("test");
    size_t index;

    memset(table, 0, sizeof(sh_symbols_t));
    sh_symbols_set(table, name, value);
    index = sh_symbols_hash(table, name);
    sh_symbols_unset(table, "name");
    if (table->data[index].name != NULL) {
        cr_assert_str_neq(table->data[index].name, "name",
            "SIMPLE SYMBOLS UNSET | Excepted to not have data after unset.");
    }
}

Test(symbols_unset, null_capacity_unset) {
    sh_symbols_t *table = malloc(sizeof(sh_symbols_t));
    char *name = strdup("name");
    char *value = strdup("test");
    size_t index;

    memset(table, 0, sizeof(sh_symbols_t));
    sh_symbols_set(table, name, value);
    index = sh_symbols_hash(table, name);
    table->capacity = 0;
    sh_symbols_unset(table, "name");
    cr_assert_str_eq(table->data[index].name, "name",
        "NULL CAPACITY SYMBOLS UNSET | Excepted to keep data after unset with 0 to capacity.");
}
