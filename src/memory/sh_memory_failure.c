/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_memory_failure
*/

#include <42sh/memory.h>
#include <42sh/io.h>
#include <stdlib.h>


/*
** Function to exit the program
** with the appropriate error message and
** exit status.
*/
void sh_memory_failure(void)
{
    sh_puterr("Critical memory failure.\n");
    exit(SH_CRITICAL_MEMFAIL);
}
