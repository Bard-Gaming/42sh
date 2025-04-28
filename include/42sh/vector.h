/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for everything
** related to vectors. The goal
** of vectors is that they can
** be used like standard C++ vectors.
*/

#ifndef SHELL_VECTOR_H
    #define SHELL_VECTOR_H

    #define SH_VEC_INIT_CAP (1 << 4)
    #define SH_VEC_GROWTH_FACTOR 1.5f

    #include <42sh/types.h>
    #include <stddef.h>


/*
** NULL-terminated dynamic array (vector).
** Automatically reallocates memory to
** fit the required data.
*/
struct sh_vector {
    void **data;
    size_t count;
    size_t capacity;
};


void sh_vector_append_range(sh_vector_t *vector, const sh_vector_t *range);
void sh_vector_delete(sh_vector_t *vector, free_fnc_t free_data);
void sh_vector_push_back(sh_vector_t *vector, void *data);
void sh_vector_reserve(sh_vector_t *vector, size_t new_cap);


#endif
