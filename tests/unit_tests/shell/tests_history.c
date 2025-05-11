/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for history
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <42sh/io.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(shell_history, .init = init_tests, .fini = end_tests);

Test(shell_history, add_element_history) {
    shell_init(data);
    int start_size = shell_history_count();
    shell_history_add("test");
    int end_size = shell_history_count();

    cr_assert_eq(end_size, (start_size + 1),
        "ADD ELEMENT HISTORY | Expected to have right count of commands in the history.");
}

Test(shell_history, get_element_history) {
    shell_init(data);
    shell_history_add("test");
    char *last_element = shell_history_get(1);

    cr_assert_str_eq(last_element, "test",
        "GET ELEMENT HISTORY | Expected to have the last command added in the history.");
}

Test(shell_history, get_element_0_history) {
    shell_init(data);
    char *last_element = shell_history_get(0);

    cr_assert_null(last_element,
        "GET ELEMENT 0 HISTORY | Expected to have NULL for the captured element.");
}
