/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_reserve
*/

#include <42sh/vector.h>
#include <42sh/memory.h>


/*
** Reserves the necessary memory to store
** at least new_cap elements inside of the
** vector.
** If the new capacity is 0, the default
** capacity growth will be applied to the
** vector instead.
*/
void sh_vector_reserve(sh_vector_t *vector, size_t new_cap)
{
    if (new_cap == 0) {
        new_cap = vector->capacity != 0 ?
        vector->capacity * SH_VEC_GROWTH_FACTOR :
        SH_VEC_INIT_CAP;
    }
    ;
    if (new_cap <= vector->capacity)
        return;
    ;
    vector->data = shreallocarray(vector->data, new_cap, sizeof(void *));
    vector->capacity = new_cap;
}
