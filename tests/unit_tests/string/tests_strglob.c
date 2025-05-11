/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for str_glob
** string
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(str_glob, .init = init_tests, .fini = end_tests);

Test(str_glob, point_str_glob) {
    char *output = sh_strglob(".", 1);

    cr_assert_str_eq(output, ".",
        "POINT STR GLOB | Expected for output : '.'");
}

Test(str_glob, star_str_glob) {
    char *output = sh_strglob("*", 1);

    cr_assert_not_null(strstr(output, "main.c"),
        "STAR STR GLOB | Expected for output : all files and folders of current dir.");
}

Test(str_glob, hidden_files_str_glob) {
    system("touch .hidden");
    char *output = sh_strglob(".*", 1);
    system("rm -f .hidden");

    cr_assert_not_null(strstr(output, ".hidden"),
        "HIDDEN FILES STR GLOB | Expected to return all hidden files.");
}
