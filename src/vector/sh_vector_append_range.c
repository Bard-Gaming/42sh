/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_append_range
*/

#include <42sh/vector.h>
#include <string.h>


/*
** Grows the vector by the growth factor
** until it is large enough to fit n new elements.
*/
static void grow_vector(sh_vector_t *vector, size_t n)
{

    size_t new_cap = vector->capacity;

    while (vector->count + n + 1 >= new_cap)
        new_cap *= SH_VEC_GROWTH_FACTOR;
    sh_vector_reserve(vector, new_cap);
}

/*
** Adds a copy of the elements of
** the second vector to the first vector.
**
** Note: THIS FUNCTION ONLY WORKS IF THE SECOND
** VECTOR CONTAINS ONLY NULL TERMINATED DATA!
**
** Technical Addendum:
** The <end> variable exists for cases when
** <vector> and <range> point to the same vector,
** and increasing the vector's count would otherwise
** increase the for loop's end bound.
*/
void sh_vector_append_range(sh_vector_t *vector, const sh_vector_t *range)
{
    size_t end = range->count;

    if (vector->count + range->count + 1 >= vector->capacity)
        grow_vector(vector, range->count);
    for (size_t i = 0; i < end; i++) {
        vector->data[vector->count] = strdup(range->data[i]);
        vector->count++;
    }
    vector->data[vector->count] = NULL;
}
