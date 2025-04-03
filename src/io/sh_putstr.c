/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_putstr
*/

#include <mysh/io.h>


void sh_putstr(const char *restrict str)
{
    sh_dputs(1, str);
}
