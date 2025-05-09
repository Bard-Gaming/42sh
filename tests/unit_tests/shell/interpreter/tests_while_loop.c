/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for while_loop
** shell
*/

#include "../../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(while_loop, .init = init_tests, .fini = end_tests);

Test(while_loop, basic_while_loop) {
    shell_system("set i = test ; while ( $i != testaaa ) ; echo $i ; set i = \"${i}a\" ; end", data);

    cr_assert_stdout_eq_str("test\ntesta\ntestaa\n",
        "BASIC WHILE LOOP | Expected to print : '0, 1, 2'.");
}
