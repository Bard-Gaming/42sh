/*
** EPITECH PROJECT, 2025
** Project - Amazed
** File description:
** Implementation for
** sh_vector_push_back
*/

#include <42sh/vector.h>


/*
** Adds the given data to the vector,
** automatically reallocating the vector's
** internal data buffer if necessary.
*/
void sh_vector_push_back(sh_vector_t *vector, void *data)
{
    if (vector->count + 1 >= vector->capacity)
        sh_vector_reserve(vector, 0);
    vector->data[vector->count] = data;
    vector->count++;
    vector->data[vector->count] = NULL;
}
