/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shmalloc
*/

#include <42sh/memory.h>
#include <stdlib.h>


/*
** Multishell's succeed or die variant
** of the standard library's malloc()
** function.
*/
void *shmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        sh_memory_failure();
    return ptr;
}
