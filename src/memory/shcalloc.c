/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shcalloc
*/

#include <42sh/memory.h>
#include <stdlib.h>


/*
** Multishell's succeed or die variant
** of the standard library's calloc()
** function.
*/
void *shcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);

    if (ptr == NULL)
        sh_memory_failure();
    return ptr;
}
