/*
** EPITECH PROJECT, 2025
** Project - Amazed
** File description:
** Implementation for
** sh_vector_push_back
*/

#include <42sh/vector.h>
#include <stdbool.h>
#include <stdlib.h>


/*
** Grows a vector by SH_VEC_GROWTH_FACTOR,
** increasing its internal capacity.
*/
static bool grow_vector(sh_vector_t *vector)
{
    vector->capacity = vector->capacity == 0 ?
        SH_VEC_INIT_CAP :
        vector->capacity * SH_VEC_GROWTH_FACTOR;
    ;
    vector->data = reallocarray(
        vector->data,
        vector->capacity,
        sizeof(void *)
    );
    return vector->data != NULL;
}

/*
** Adds the given data to the vector,
** automatically reallocating the vector's
** internal data buffer if necessary.
** Does nothing on failure.
*/
void sh_vector_push_back(sh_vector_t *vector, void *data)
{
    if (vector->count + 1 >= vector->capacity)
        if (!grow_vector(vector))
            return;
    vector->data[vector->count] = data;
    vector->count++;
    vector->data[vector->count] = NULL;
}
