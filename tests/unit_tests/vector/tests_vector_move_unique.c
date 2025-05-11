/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for vector_move_unique
** vector
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/vector.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <limits.h>


extern sh_data_t *data;


TestSuite(vector_move_unique, .init = init_tests, .fini = end_tests);

Test(vector_move_unique, move_unique_element) {
    sh_vector_t vector1 = { 0 };
    sh_vector_t vector2 = { 0 };
    char *data1 = strdup("test1");
    char *data2 = strdup("test1");
    char *data3 = strdup("test2");
    sh_vector_push_back(&vector1, data1);
    sh_vector_push_back(&vector2, data2);
    sh_vector_push_back(&vector2, data3);
    sh_vector_move_unique(&vector1, &vector2);

    cr_assert_str_eq(vector1.data[vector1.count - 1], data3,
        "VECTOR MOVE UNIQUE | Expected as last data element in vector1 : last data element of vector2.");
    cr_assert_eq(vector2.count, 0,
        "VECTOR MOVE UNIQUE | Expected to have no data elements in vector2 after move_unique function.");
}
