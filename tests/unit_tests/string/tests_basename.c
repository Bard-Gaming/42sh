/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for basename
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(basename, .init = init_tests, .fini = end_tests);

Test(basename, default_basename) {
    char *basename = sh_basename(NULL);
    char *excepted_path = capture_stdout("basename \"$PWD\"");
    strtok(excepted_path, "\n");

    cr_assert_str_eq(basename, excepted_path,
        "DEFAULT BASENAME | Expected current path.");
}
