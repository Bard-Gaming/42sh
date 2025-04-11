/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_delete
*/

#include <42sh/vector.h>
#include <stdlib.h>


/*
** Deletes a vector and resets it back to
** a NULL initialized state (meaning it can
** be used again after this call).
** No errors are possible.
** If the given free_data function is NULL,
** free() is used instead.
** Does nothing if the given vector pointer
** is NULL.
*/
void sh_vector_delete(sh_vector_t *vector, free_fnc_t free_data)
{
    if (vector == NULL)
        return;
    free_data = free_data ?: free;
    for (size_t i = 0; i < vector->count; i++)
        free_data(vector->data[i]);
    free(vector->data);
    *vector = (sh_vector_t){ 0 };
}
