/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for vector_glob
** vector
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/vector.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(vector_glob, .init = init_tests, .fini = end_tests);

Test(vector_glob, empty_vector_glob) {
    sh_vector_t vector = { 0 };
    sh_vector_glob(&vector, 0);

    cr_assert_eq(vector.count, 0,
        "EMPTY VECTOR GLOB | No modifications should be made when the input vector is empty.");
}

Test(vector_glob, sanitize_vector_glob) {
    sh_vector_t vector = { 0 };
    char *data1 = strdup(".");
    char *data2 = strdup("..");
    sh_vector_push_back(&vector, data1);
    sh_vector_push_back(&vector, data2);
    sh_vector_glob(&vector, true);

    for (size_t i = 0; i < vector.count; i++) {
        cr_assert_str_neq(vector.data[i], ".",
            "SANITIZE VECTOR GLOB | '.' should have been removed.");
        cr_assert_str_neq(vector.data[i], "..",
            "SANITIZE VECTOR GLOB | '..' should have been removed.");
    }
}
