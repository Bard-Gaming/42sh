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
** Pops the element at index from the vector
** without deleting it.
*/
static void *pop_element(sh_vector_t *vector, size_t index)
{
    void *popped = vector->data[index];

    vector->count--;
    vector->data[index] = vector->data[vector->count];
    return popped;
}

/*
** Tells whether or not the vector contains
** the element described by ref.
*/
static bool contains(sh_vector_t *vector, const void *ref)
{
    for (size_t i = 0; i < vector->count; i++) {
        if (strcmp(vector->data[i], ref) == 0)
            return true;
    }
    return false;
}

/*
** Moves all elements from range into vector,
** if they aren't already in vector.
** The range vector will get deleted afterwards,
** no matter how many unique elements are present.
** This currently only works with null-terminated
** elements.
*/
void sh_vector_move_unique(sh_vector_t *vector, sh_vector_t *range)
{
    void *element;

    while (range->count > 0) {
        element = pop_element(range, 0);
        if (!contains(vector, element))
            sh_vector_push_back(vector, element);
        else
            free(element);
    }
    sh_vector_delete(range, NULL);
}
