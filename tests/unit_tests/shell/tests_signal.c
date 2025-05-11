/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for signal_interrupt
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(signal_interrupt, .init = init_tests, .fini = end_tests);

Test(signal_interrupt, signal_interrupt_basic) {
    shell_init(data);
    signal_interrupt(-1);

    cr_assert_stderr_eq_str("",
        "BASIC SIGNAL INTERRUPT | Expected no output for this func.");
}