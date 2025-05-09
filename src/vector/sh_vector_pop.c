/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_pop
*/

#include <42sh/vector.h>


/*
** Pops an element from the given vector.
** If the element is out of range, NULL
** is returned instead.
*/
void *sh_vector_pop(sh_vector_t *vector, size_t index)
{
    void *element;

    if (index >= vector->count)
        return NULL;
    element = vector->data[index];
    for (size_t i = index; i < vector->count; i++)
        vector->data[i] = vector->data[i + 1];
    vector->count--;
    return element;
}
