/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shreallocarray
*/

#include <42sh/memory.h>
#include <stdlib.h>


/*
** Multishell's succeed or die variant
** of the standard library's reallocarray()
** function.
*/
void *shreallocarray(void *ptr, size_t nmemb, size_t size)
{
    void *resptr = reallocarray(ptr, nmemb, size);

    if (resptr == NULL && size != 0 && nmemb != 0)
        sh_memory_failure();
    return resptr;
}
