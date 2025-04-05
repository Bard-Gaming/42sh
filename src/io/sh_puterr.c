/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_puterr
*/

#include <mysh/io.h>


/*
** This utility function is used to write a
** message to the standard error output.
*/
void sh_puterr(const char *restrict err)
{
    sh_dputs(2, err);
}
