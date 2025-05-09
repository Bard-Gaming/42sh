/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_move_unique
*/

#include <42sh/vector.h>
#include <string.h>
#include <stdlib.h>


/*
** Grows the vector by the growth factor
** until it is large enough to fit n new elements.
*/
static void grow_vector(sh_vector_t *vector, size_t n)
{
    size_t new_cap = vector->capacity ?: SH_VEC_INIT_CAP;

    while (vector->count + n + 1 >= new_cap)
        new_cap *= SH_VEC_GROWTH_FACTOR;
    sh_vector_reserve(vector, new_cap);
}

/*
** Moves all elements from range into vector.
** The range vector will get deleted afterwards.
*/
void sh_vector_move(sh_vector_t *vector, sh_vector_t *range)
{
    if (vector->count + range->count + 1 >= vector->capacity)
        grow_vector(vector, range->count);
    for (size_t i = 0; i < range->count; i++) {
        vector->data[vector->count] = range->data[i];
        vector->count++;
    }
    vector->data[vector->count] = NULL;
    free(range->data);
    memset(range, 0, sizeof(sh_vector_t));
}
