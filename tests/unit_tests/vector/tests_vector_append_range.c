/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for vector_append_range
** vector
*/

#include <42sh/data.h>
#include <42sh/vector.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(vector_append_range, .init = init_tests, .fini = end_tests);

Test(vector_append_range, basic_append) {
    sh_vector_t *vector1 = malloc(sizeof(sh_vector_t));
    sh_vector_t *vector2 = malloc(sizeof(sh_vector_t));
    memset(vector1, 0, sizeof(sh_vector_t));
    memset(vector2, 0, sizeof(sh_vector_t));
    char *data1 = "test1";
    char *data2 = "test2";
    sh_vector_push_back(vector1, data1);
    sh_vector_push_back(vector2, data2);
    sh_vector_append_range(vector1, vector2);

    cr_assert_str_eq(vector1->data[vector1->count - 1], data2,
        "BASIC VECTOR APEND | Excepted as last data element in vector1 : last data element of vector2.");
}

Test(vector_append_range, too_small_vector_append) {
    sh_vector_t *vector1 = malloc(sizeof(sh_vector_t));
    sh_vector_t *vector2 = malloc(sizeof(sh_vector_t));
    memset(vector2, 0, sizeof(sh_vector_t));
    char *data1 = "test1";
    sh_vector_push_back(vector2, data1);
    sh_vector_append_range(vector1, vector2);

    cr_assert_str_eq(vector1->data[vector1->count - 1], data1,
        "TOO SMALL VECTOR APEND | Excepted a successful append even when vector1 is too small.");
}
