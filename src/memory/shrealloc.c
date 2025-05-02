/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shrealloc
*/

#include <42sh/memory.h>
#include <stdlib.h>


/*
** Multishell's succeed or die variant
** of the standard library's realloc()
** function.
*/
void *shrealloc(void *ptr, size_t size)
{
    void *resptr = realloc(ptr, size);

    if (resptr == NULL && size != 0)
        sh_memory_failure();
    return resptr;
}
